#include "client.h"
#include "socket.h"

char data[1024];
int val_write;
int val_read;
int main()
{
    if (create_TCP_IPv4_client(&client_fd, &len) == ERROR)
    {
        return -1;
    }
    if (connect_to_TCP_IPv4_server(&server_address, "192.168.27.167", PORT, &client_fd, &len) == ERROR)
    {
        return -1;
    }
    int i = 0;
    do
    {
        i++;
        val_read = readn(client_fd, data, 1024);
        if (i > 4)
        {
            return -1;
        }
    } while (val_read == 0);

    printf("Number of bytes received:%d\n", val_read);

    val_write = writen(client_fd, "Client has received message\n", 29);

    close(client_fd);

    printf("Data received:\n%s\n", data);
    return 0;
}