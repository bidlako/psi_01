#include "tcp_server.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long port = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || port <= 0 || port > 65535) {
        printf("Please provide a valid port number (1-65535).\n");
        return 1;
    }

    ServerConfig config = {
            .ip_address = "127.0.0.1",
            .port = (unsigned int)port
    };

    int server_fd = init_server(&config);
    if (server_fd == -1) {
        return 1;
    }

    if (start_server(server_fd) == -1) {
        close(server_fd);
        return 1;
    }

    close(server_fd);
    return 0;
}

