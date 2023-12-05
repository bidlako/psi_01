#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

typedef struct {
    const char *ip_address;
    unsigned int port;
} ServerConfig;

typedef struct {
    int socket_fd;
    struct sockaddr_in address;
} ClientConnection;

int init_server(const ServerConfig *config);

int start_server(int server_fd);

void *handle_client(void *client);

#endif /* TCP_SERVER_H */
