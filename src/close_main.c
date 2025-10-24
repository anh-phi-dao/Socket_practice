#include "client.h"
#include "socket.h"
#include <sys/poll.h>

#define SERVER_IP "192.168.27.167"

char buff[1024];
char file_name[100];
int val_write;
int val_read;

int main()
{
    if (create_TCP_IPv4_client(&client_fd, &len) == ERROR)
    {
        return -1;
    }

    if (connect_to_TCP_IPv4_server(&server_address, SERVER_IP, PORT, &client_fd, &len) == ERROR)
    {
        return -1;
    }
    do
    {
        val_write = writen(client_fd, "Close", 6);
        val_read = readn(client_fd, buff, 1024);
        printf("%s", buff);
        sleep(1);
    } while (val_read > 0);

    close(client_fd);

    return 0;
}