#include "tcp_server.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>

int init_server(const ServerConfig *config) {
    int server_fd;
    struct sockaddr_in server_address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Failed to create socket");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(config->port);
    inet_pton(AF_INET, config->ip_address, &server_address.sin_addr);

    if (bind(server_fd, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        perror("Failed to bind");
        close(server_fd);
        return -1;
    }

    return server_fd;
}

int start_server(int server_fd) {
    if (listen(server_fd, 5) == -1) {
        perror("Failed to listen");
        return -1;
    }

    struct sockaddr_in local_address;
    socklen_t addr_length = sizeof(local_address);

    if (getsockname(server_fd, (struct sockaddr *) &local_address, &addr_length) == -1) {
        perror("getsockname failed");
        close(server_fd);
        return 1;
    }

    printf("Server listening on port %d\n", ntohs(local_address.sin_port));

    for(;;) {
        ClientConnection *client = malloc(sizeof(ClientConnection));
        socklen_t client_addr_len = sizeof(client->address);
        client->socket_fd = accept(server_fd, (struct sockaddr *) &client->address, &client_addr_len);
        if (client->socket_fd == -1) {
            perror("Failed to accept");
            free(client);
            continue;
        }

        printf("Client connected: %s:%d\n", inet_ntoa(client->address.sin_addr), ntohs(client->address.sin_port));
        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, client);
        pthread_detach(client_thread);
    }

    return 0;
}

void* handle_client(void *arg) {
    ClientConnection *client = (ClientConnection *) arg;
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE + strlen("You wrote: ") + 1];

    for(;;) {
        ssize_t bytes_received = recv(client->socket_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                printf("Client %s:%d disconnected gracefully.\n", inet_ntoa(client->address.sin_addr), ntohs(client->address.sin_port));
            } else if (errno == ECONNRESET) {
                printf("Client %s:%d reset the connection.\n", inet_ntoa(client->address.sin_addr), ntohs(client->address.sin_port));
            } else {
                perror("Failed to receive");
            }
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Client %s:%d wrote: %s", inet_ntoa(client->address.sin_addr), ntohs(client->address.sin_port), buffer);

        snprintf(response, sizeof(response), "You wrote: %s", buffer);
        if (send(client->socket_fd, response, strlen(response), 0) == -1) {
            perror("Failed to send response");
            break;
        }
    }

    shutdown(client->socket_fd, SHUT_RDWR);
    close(client->socket_fd);
    free(client);

    return NULL;
}

