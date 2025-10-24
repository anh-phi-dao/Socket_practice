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
#define MAXIMUM_CLIENT 1

extern struct sockaddr_in server_address;
extern socklen_t len;
extern int client_fd;

int create_TCP_IPv4_client(int *client_fd, socklen_t *len);
int connect_to_TCP_IPv4_server(struct sockaddr_in *server_addr, char *IPv4, uint16_t port, int *client_fd, socklen_t *len);

enum
{
    ERROR = -1,
    SUCCESS
};