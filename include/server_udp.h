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

/**
 * @brief Create a UDP server, user can choose the PORT, number of clients that server can connect
 * @param server_addr: pointer to server address following IPv4, the function will create a server that can received
 * any client address and the information will be stored in server address. Users can use predefined struct sockaddr_in server
 * @param port: port number, this is a parameter belongs to transport layer of OSI model. User can use predefined PORT =8000
 * @param num_of_client: maximum number that client can receive. Users can use predefined MAXIMUM_CLIENT = 10
 * @param fd: A pointer that points to the file descriptor of the server socket. User can use predefined int server_fd
 * @param len: a pointer to socken_t which store the length of the address (IPv4 is different, IPv6 is different)
 * . Users can use predefined socklen_t len;
 * @return SUCCESS=0, ERROR=-1
 */
int create_UDP_IPv4_server(struct sockaddr_in *server_addr, uint16_t port, int *server_fd, socklen_t *len);
/**
 * @brief Create client address for UDP connection
 * @param client_addr: pointer to client address following IPv4. The port and IPv4 information will be stored in this strruct
 * in network format.
 * @param IPv4: a pointer pointing to a char array which contains IPv4 address in human-reable string
 * @param port: port number, this is a parameter belongs to transport layer of OSI model. User can use predefined PORT =8000
 * @return SUCCESS=0, ERROR=-1
 */
int create_UDP_IPv4_client_address(struct sockaddr_in *client_addr, char *IPv4, uint16_t port);

enum
{
    ERROR = -1,
    SUCCESS
};