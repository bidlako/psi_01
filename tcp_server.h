#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdbool.h>
#include <netinet/tcp.h>

#define BUFFER_SIZE 1024

/* Server configuration structure */
typedef struct {
    const char *ip_address;
    unsigned int port;
} ServerConfig;

/* Client structure to represent an individual client connection */
typedef struct {
    int socket_fd;
    struct sockaddr_in address;
} ClientConnection;

/* Initialize the server */
int init_server(const ServerConfig *config);

/* Start the server to listen and accept client connections */
int start_server(int server_fd);

/* Handle an individual client connection */
void *handle_client(void *client);

#endif /* TCP_SERVER_H */
