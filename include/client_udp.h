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

extern socklen_t len;
/**
 * @brief Create UDP client
 * @param client_fd: a pointer which point to a file descriptor coresponding to client UDP socket.
 * User can use predefined int client_udp_fd
 * @return ERROR = -1, SUCCESS = 0
 */
int create_UDP_IPv4_client(int *client_fd);
/**
 * @brief Create server address for server UDP connection
 * @param client_addr: pointer to server address following IPv4. The port and IPv4 information will be stored in this strruct
 * in network format.
 * @param IPv4: a pointer pointing to a char array which contains IPv4 address in human-reable string
 * @param port: port number, this is a parameter belongs to transport layer of OSI model. User can use predefined PORT =8000
 * @return SUCCESS=0, ERROR=-1
 */
int create_UDP_IPv4_server_address(struct sockaddr_in *server_addr, char *IPv4, uint16_t port);

enum
{
    ERROR = -1,
    SUCCESS
};