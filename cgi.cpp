#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

// Mini CGI execution function
std::string executeCGI(const std::string& scriptPath, const std::string& interpreterPath, const std::string& requestBody) {
    int inputPipe[2];
    int outputPipe[2];
    
    // Create dual pipes for bidirectional communication
    // inputPipe: Parent writes [1] -> Child reads [0] (acts as stdin)
    // outputPipe: Child writes [1] -> Parent reads [0] (acts as stdout)
    if (pipe(inputPipe) == -1 || pipe(outputPipe) == -1) {
        return "Error creating pipes";
    }

    pid_t pid = fork();
    if (pid == -1) {
        return "Error forking";
    }

    if (pid == 0) { // --- Child process ---
        // Bind the child's STDIN to read from the input pipe
        dup2(inputPipe[0], STDIN_FILENO);
        // Bind the child's STDOUT to write to the output pipe
        dup2(outputPipe[1], STDOUT_FILENO);

        // Close unused pipe ends in the child
        close(inputPipe[1]);
        close(outputPipe[0]);
        close(inputPipe[0]); // Already duplicated to 0
        close(outputPipe[1]); // Already duplicated to 1

        // 1. Prepare minimal Environment Variables
        std::string contentLength = "CONTENT_LENGTH=" + std::to_string(requestBody.length());
        
        const char* envp[] = {
            "REQUEST_METHOD=POST",
            "GATEWAY_INTERFACE=CGI/1.1",
            contentLength.c_str(),
            NULL
        };

        // 2. Prepare Arguments for Python execution
        const char* args[] = {
            interpreterPath.c_str(),
            scriptPath.c_str(),
            NULL
        };

        // Execute the script
        execve(interpreterPath.c_str(), const_cast<char* const*>(args), const_cast<char* const*>(envp));
        
        // If execve fails, it drops here
        std::cerr << "execve failed!" << std::endl;
        _exit(1);
    } 
    else { // --- Parent process ---
        // Close unused ends in parent (Parent only WRITES to input, READS from output)
        close(inputPipe[0]);
        close(outputPipe[1]);

        // 1. Send the Request Body
        if (!requestBody.empty()) {
            write(inputPipe[1], requestBody.c_str(), requestBody.length());
        }
        close(inputPipe[1]); // Close immediately so the CGI knows STDIN EOF is reached!

        // 2. Read the CGI Response
        std::string response;
        char buffer[1024];
        ssize_t bytesRead;
        while ((bytesRead = read(outputPipe[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            response += buffer;
        }
        close(outputPipe[0]); // Done reading

        // 3. Wait for the child to finish to avoid zombie processes
        int status;
        waitpid(pid, &status, 0);

        return response;
    }
}

int main() {
    // ---------------------------------------------------------
    // Make sure you have a python file named "test.py" mapping 
    // to your correct location for you to test this.
    // ---------------------------------------------------------
    std::string script = "./test.py"; // Example path to script
    std::string interpreter = "/usr/bin/python3"; // Find exactly where python is, e.g. /usr/bin/python
    std::string body = "name=John Doe&message=HelloFromCGI!";

    std::cout << "Starting standalone CGI execution..." << std::endl;
    std::string output = executeCGI(script, interpreter, body);
    
    std::cout << "--- CGI Output ---" << std::endl;
    std::cout << output << std::endl;
    std::cout << "------------------" << std::endl;
    
    return 0;
}
