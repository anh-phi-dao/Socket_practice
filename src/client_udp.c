#include "client_udp.h"

int client_udp_fd;

struct sockaddr_in server;

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