#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // flush stdin
}

int start_ssh_connection(const char *serverIp, const char *username, const char *password) {
    ssh_session session = ssh_new(); // create new ssh connection
    if (!session) {
        fprintf(stderr, "\nFailed to create SSH session\n");
        return -1;
    }

    // set SSH connection options
    ssh_options_set(session, SSH_OPTIONS_HOST, serverIp);
    ssh_options_set(session, SSH_OPTIONS_USER, username);

    // connect to the SSH server
    if (ssh_connect(session) != SSH_OK) {
        fprintf(stderr, "\nConnection failed: %s\n", ssh_get_error(session));
        ssh_free(session);
        return -1;
    }

    // authenticate using provided password
    if (ssh_userauth_password(session, NULL, password) != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "\nAuthentication failed: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return -1;
    }

    printf("\nSuccessfully connected to %s@%s!\n", username, serverIp);

    printf("\nPRESS ENTER TO EXIT\n");
    getchar();

    // close SSH session
    // ssh_disconnect(session);
    // ssh_free(session);
    return 0;
}

int main() {
    char serverIp[128], username[128], password[128], confirm;

    while (1) { // Keep looping until valid input is confirmed
        // Get SSH server address
        printf("Please enter SSH server address: ");
        fgets(serverIp, sizeof(serverIp), stdin);
        serverIp[strcspn(serverIp, "\n")] = 0; // Remove newline

        // Get username
        printf("Please enter username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0; // Remove newline

        // Get password
        printf("Please enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0; // Remove newline

        // Confirm details
        printf("\nSSH Connection Info:\n");
        printf("Server: %s\nUsername: %s\n", serverIp, username);
        printf("Proceed with connection? (y/n): ");
        scanf(" %c", &confirm);
        clear_input_buffer(); // Clear any leftover input

        if (confirm == 'y' || confirm == 'Y') {
            if (start_ssh_connection(serverIp, username, password) == 0) {
                break; // Exit loop if connection is successful
            } else {
                printf("\nConnection failed. Please re-enter your details.\n\n");
            }
        } else {
            printf("\nRestarting input process...\n\n");
        }
    }

    return 0;
}
