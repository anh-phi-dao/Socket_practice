#include "server_udp.h"

int server_udp_fd;

struct sockaddr_in server;
struct sockaddr_in client;

socklen_t len = (socklen_t)sizeof(struct sockaddr_in);

int create_UDP_IPv4_server(struct sockaddr_in *server_addr, uint16_t port, int *server_fd, socklen_t *len)
{
    *server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*server_fd < 0)
    {
        *server_fd = 0;
        printf("Failed on socket function\n");
        return ERROR;
    }

    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(port);
    server_addr->sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        printf("Failed on setsockopt function\n");
        return ERROR;
    }
    if (bind(*server_fd, (struct sockaddr *)server_addr, *len) < 0)
    {
        printf("Failed on binding a server\n");
        return ERROR;
    }

    printf("Successfully created UDP server\n");
    return SUCCESS;
}

int create_UDP_IPv4_client_address(struct sockaddr_in *client_addr, char *IPv4, uint16_t port)
{
    client_addr->sin_family = AF_INET;
    client_addr->sin_port = htons(port);
    if (inet_pton(AF_INET, IPv4, &client_addr->sin_addr) <= 0)
    {
        printf("Invalid address\n");
        return ERROR;
    }
    printf("Successfully created UDP client address\n");
    return SUCCESS;
}