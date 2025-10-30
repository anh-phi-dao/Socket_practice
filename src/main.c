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
    while (1)
    {
        printf("Please enter the file: ");
        scanf("\n");
        scanf("%100[^\n]s", file_name);
        val_write = writen(client_fd, file_name, 100);
        if (val_write != 100)
        {
            printf("Send file name to server has failed, please send again\n");
            continue;
        }
        else
        {
            printf("\nNumber of bytes have been sent :%d\n\n", val_write);
        }

        for (int i = 0; i < 5; i++)
        {

            val_read = read(client_fd, buff, 1024);
            if (val_read > 0)
            {
                printf("Num of bytes read %d\n", val_read);
                break;
            }
            else if (i == 4 && val_read == 0)
            {
                printf("Server has closed\n");
                close(client_fd);
                return -1;
            }
            sleep(1);
        }

        printf("Read %s from server:\n\n%s", file_name, buff);
    }
    return 0;
}