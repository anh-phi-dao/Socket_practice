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

extern int server_udp_fd;
extern struct sockaddr_in server;
extern struct sockaddr_in client;
extern socklen_t len;

int create_UDP_IPv4_server(struct sockaddr_in *server_addr, uint16_t port, int *server_fd, socklen_t *len);
int create_UDP_IPv4_client_address(struct sockaddr_in *client_addr, char *IPv4, uint16_t port);

enum
{
    ERROR = -1,
    SUCCESS
};