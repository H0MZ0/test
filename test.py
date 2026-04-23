import sys
import os

print("Content-Type: text/plain\r\n")

# Reading Environment Variable
print(f"REQUEST_METHOD: {os.environ.get('REQUEST_METHOD')}")

# Reading the Body from STDIN
body = sys.stdin.read()
print(f"BODY READ FROM STDIN: {body}")
