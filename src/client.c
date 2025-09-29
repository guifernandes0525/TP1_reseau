#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

void remove_spaces(char* s) {
        char* d = s;
        do {
            while (*d == ' ') {
                ++d;
            }
        } while (*s++ = *d++);
    }

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("2 input is needed : ./clientCalc IPServer Port\n");
        return -1;
    }

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) {
        printf("Error during socket creating process\n");
        return -1;
    }

    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = argv[1];
    serv_addr.sin_port = htons(argv[2]);

    if (inet_pton(&serv_addr.sin_family, &serv_addr.sin_addr.s_addr, &serv_addr.sin_addr) <= 0) {
        printf("Invalid adress\n");
        return -1;
    }

    if (connect(client_socket, &serv_addr, sizeof(serv_addr)) != 0) {
        printf("Error during connection with the server");
        return -1;
    }

    char* send_buffer = (char*) malloc(1024*sizeof(char));
    char* recv_buffer = (char*) malloc(1024*sizeof(char));

    while (1) {
        printf("Enter the calcul : ");

        if (fgets(send_buffer, 1024, stdin) == NULL) {
            fprintf(stderr, "Error reading\n");
            break;
        }

        send_buffer[strcspn(send_buffer, "\n")] = '\0';

        remove_spaces(send_buffer);

        printf("%s", send_buffer);

        if (strcmp(send_buffer, "quit") == 0) break;

        size_t len = strlen(send_buffer);
        if (write(client_socket, send_buffer, len) == -1) {
            printf("Error during message sending");
            break;
        }

        if (read(client_socket, recv_buffer, 1023)) {
            printf("Error during message reception");
            break;
        }

        recv_buffer[1024 - 1] = '\0';

        printf("%s\n", recv_buffer);
    }

    close(client_socket);
    free(send_buffer);
    free(recv_buffer);

    return 0;
}