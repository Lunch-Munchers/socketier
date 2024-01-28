// simple_socket_program.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int create_server_socket(int port) {
    int server_socket;
    struct sockaddr_in server_addr;

    // Creating socket file descriptor
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Binding the socket to a specific address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_socket, 1) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    return server_socket;
}

int accept_client(int server_socket) {
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Accepting incoming connections
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    return client_socket;
}

int connect_to_server(const char *server_ip, int port) {
    int client_socket;
    struct sockaddr_in server_addr;

    // Creating socket file descriptor
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connecting to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    return client_socket;
}

void send_data(int socket, const char *data) {
    send(socket, data, strlen(data), 0);
}

void receive_data(int socket, char *buffer) {
    memset(buffer, 0, MAX_BUFFER_SIZE);
    recv(socket, buffer, MAX_BUFFER_SIZE, 0);
}

void close_socket(int socket) {
    close(socket);
}

void cleanup_server(int server_socket) {
    close(server_socket);
}

void cleanup_client(int client_socket) {
    close(client_socket);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <type (listening(2) or sending(1))> <port> <ip (optional)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int type = atoi(argv[1]);
    int port = atoi(argv[2]);
    const char *ip = (argc == 4) ? argv[3] : "127.0.0.1";

    if (type == 1) { // Sending
        int client_socket = connect_to_server(ip, port);

        char message[MAX_BUFFER_SIZE];
        while (1) {
            printf("Enter message (press Enter with an empty text field to exit): ");
            fgets(message, MAX_BUFFER_SIZE, stdin);

            // Remove trailing newline
            size_t len = strlen(message);
            if (len > 0 && message[len - 1] == '\n') {
                message[len - 1] = '\0';
            }

            if (strlen(message) == 0) {
                break;
            }

            send_data(client_socket, message);
        }

        cleanup_client(client_socket);
    } else if (type == 2) { // Listening
        int server_socket = create_server_socket(port);
        printf("Listening on port %d...\n", port);

        int client_socket = accept_client(server_socket);

        char buffer[MAX_BUFFER_SIZE];
        while (1) {
            receive_data(client_socket, buffer);
            printf("Received: %s\n", buffer);

            if (strlen(buffer) == 0) {
                break;
            }
        }

        cleanup_server(server_socket);
        cleanup_client(client_socket);
    } else {
        fprintf(stderr, "Invalid type. Use 1 for sending or 2 for listening.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
