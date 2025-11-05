#include "client_udp.h"

int client_udp_fd;

struct sockaddr_in server;
struct sockaddr_in client;

socklen_t len = (socklen_t)sizeof(struct sockaddr_in);

int create_UDP_IPv4_client(int *client_fd)
{
    *client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*client_fd < 0)
    {
        *client_fd = 0;
        printf("Failed on socket function\n");
        return ERROR;
    }

    printf("Successfully created UDP server\n");
    return SUCCESS;
}

int create_UDP_IPv4_client_with_specified_port(int *client_fd, struct sockaddr_in *client_addr, uint16_t port, socklen_t *len)
{
    *client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*client_fd < 0)
    {
        *client_fd = 0;
        printf("Failed on socket function\n");
        return ERROR;
    }

    client_addr->sin_family = AF_INET;
    client_addr->sin_port = htons(port);
    client_addr->sin_addr.s_addr = INADDR_ANY;

    /* data */

    int opt = 1;
    if (setsockopt(*client_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        printf("Failed on setsockopt client\n");
        return ERROR;
    }
    if (bind(*client_fd, (struct sockaddr *)client_addr, *len) < 0)
    {
        printf("Failed on binding a client\n");
        return ERROR;
    }

    printf("Successfully created UDP client\n");
    return SUCCESS;
}

int create_UDP_IPv4_server_address(struct sockaddr_in *server_addr, char *IPv4, uint16_t port)
{
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(port);
    if (inet_pton(AF_INET, IPv4, &server_addr->sin_addr) <= 0)
    {
        printf("Invalid address\n");
        return ERROR;
    }
    return SUCCESS;
}