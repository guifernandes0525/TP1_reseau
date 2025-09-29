#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#include "calculator.h"

#define INIT_PORT 22000
#define BUFF_LEN 1024
#define MAX_CLIENT 10

int main(int argc, char *argv[]) {

    int serv_port = -1;
    
    // validate the number of arguments given
    
    if (argc < 2){
        printf("It is necessary to inform the port. \n");
    }
    else {
        serv_port = atoi(argv[1]);
    }
    // server file descriptor
    int server_fd;

    // might need to change the AF_INET to local
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM is TCP
    
    if (server_fd == -1) {
        return -1;
    }

    struct sockaddr_in serv_address;
    serv_address.sin_family = AF_INET; // ipv4
    serv_address.sin_port = htons(serv_port);
    serv_address.sin_addr.s_addr = INADDR_ANY; // binds with all interfaces ()

    int opt = 1;  // Enables SO_REUSEADDR
    // SO_REUSEADDR makes it possible to reuse adress after reinitializing server
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        printf("Problem setting options for socket\n");        
        return -1;
    }
    
    socklen_t size_addr = sizeof(serv_address);

    // Used to connect the socket to the ip and port
    if (bind(server_fd, (struct sockaddr *) &serv_address, size_addr)) {
        printf("Problem binding socket\n");        
        return -1;
    }

    listen(server_fd, MAX_CLIENT);

    struct sockaddr_in client_address;

    while (true)
    {
        int calc_socket;
        socklen_t client_addr_size = sizeof(client_address);
        calc_socket = accept(server_fd, (struct sockaddr *) &client_address, &client_addr_size);
        
        if (calc_socket == -1) {
            printf("Problem accepting connection");
        }
        
        pid_t pid = fork();

        if (pid == 0) { // this is the child process
            
            close(server_fd); // child doesn’t need listener

            // Buffer
            char in_buffer[BUFF_LEN];
            char out_buffer[BUFF_LEN];

            EXPRESSION expression;
            RESULT result;

            do {
                read(calc_socket, in_buffer, sizeof(char)*BUFF_LEN);

                if (check_input(in_buffer, &expression)) {
                    printf("Invalid format for expression");
                } 
                else {
                    calculate_expression(expression, &result);
                }
                
                sprintf(out_buffer, "%.2f\n", result.result);

                write(calc_socket, out_buffer, BUFF_LEN);

            } while (0); // add the quit condition, but for now executes only once

            close(calc_socket);
            exit(0);

        }
        else if (pid > 0) { // this is the father process
            close(calc_socket);

        }
        else {
            close(calc_socket);
        }
    }

    return 0;
}