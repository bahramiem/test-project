#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 1080
#define BUFFER_SIZE 4096

int server_fd = -1;

void handle_sigint(int sig) {
    printf("\nShutting down server...\n");
    if (server_fd != -1) {
        close(server_fd);
    }
    exit(0);
}

int main() {
    int new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Register signal handler for graceful shutdown
    signal(SIGINT, handle_sigint);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 1080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", PORT);
    printf("Press Ctrl+C to stop.\n");

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("\n[Connection from %s]\n", client_ip);

        ssize_t valread;
        while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
            // Print received data to console
            fwrite(buffer, 1, valread, stdout);
            fflush(stdout); 
        }

        if (valread < 0) {
            perror("read error");
        }

        printf("\n[Connection closed]\n");
        close(new_socket);
    }

    return 0;
}
