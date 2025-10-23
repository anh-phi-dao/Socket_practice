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
#define MAXIMUM_CLIENT 10

extern struct sockaddr_in server;
extern socklen_t len;
extern int server_fd;
extern int client_fd[MAXIMUM_CLIENT];
extern char IP[INET_ADDRSTRLEN];
extern uint16_t port_number;
int create_TCP_IPv4_server(struct sockaddr_in *server_addr, uint16_t port, int num_of_client, int *fd, socklen_t *len);
int accept_client_connection(struct sockaddr_in *server_addr, int *server_fd, int *client_fd, socklen_t *len);
int get_client_information(int *client_fd, socklen_t *len);
int handling_message_for_multiple_clients(struct pollfd *fds, int *client_fd, char *buff);

enum
{
    ERROR = -1,
    SUCCESS
};