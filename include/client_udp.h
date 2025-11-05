#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*libray for socket structure*/
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8000

extern int client_udp_fd;
extern struct sockaddr_in server;
extern struct sockaddr_in client;

extern socklen_t len;

int create_UDP_IPv4_client(int *client_fd);
int create_UDP_IPv4_server_address(struct sockaddr_in *server_addr, char *IPv4, uint16_t port);
int create_UDP_IPv4_client_with_specified_port(int *client_fd, struct sockaddr_in *client_addr, uint16_t port, socklen_t *len);

enum
{
    ERROR = -1,
    SUCCESS
};