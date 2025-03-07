# sshClient
Just a simple SSH client that handles basic password-based authentication. By adding the suggested functions, Next tasks in the project include creating features to support key-based authentication, remote command execution, interactive shells, and better error handling, making it a more robust and user-friendly tool.

### prerequisites:
- libssh

---

This C program is a basic SSH client that allows a user to connect to a remote SSH server using a username and password. The program prompts the user to input the server's IP address, username, and password, and then attempts to establish an SSH connection. If the connection is successful, the program notifies the user and waits for them to press Enter before exiting. If the connection fails, the user is prompted to re-enter their details.

The program uses the libssh library to handle the SSH connection and authentication. It also includes a utility function to clear the input buffer to avoid issues with leftover input.

---

### how to install

1. use your favorite compiler to compile the main file.  i.e. for linux users:
   ```
   gcc -o ssh ssh.c -lssh
   ```
2. make the file executable
   ```
   chmod +x ssh
   ```
3. run the client
   ```
   ./ssh
   ```
