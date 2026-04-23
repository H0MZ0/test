#include <iostream>
#include <unistd.h>


using namespace std;


string executeCGI(string &script, string &interpreter, string &body){
    int in[2];
    int out[2];

    if (pipe(in) == -1 || pipe(out) == -1){
        return "pipe error";
    }

    pid_t pid = fork();

    if (pid == -1){
        return "fork error";
    }

    if (pid == 0){
        close (in[0]);
        close (in[1]);
        close (out[0]);
        close (out[1]);

        dup2(in[0], 0);
        dup2(out[1], 1);

        string CONTENT = "CONTENT_LENGHT=" + to_string(body.length());

        const char *prm[] = {
            interpreter.c_str(),
            script.c_str(),
            NULL
        };

        execve(interpreter.c_str(), const_cast<char * const *>(prm), )
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
