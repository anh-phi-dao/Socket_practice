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
    /*create an TCP client using IPv4 address*/
    if (create_TCP_IPv4_client(&client_fd, &len) == ERROR)
    {
        return -1;
    }
    /*identify the server IPv4 address and server's port*/
    if (connect_to_TCP_IPv4_server(&server_address, SERVER_IP, PORT, &client_fd, &len) == ERROR)
    {
        return -1;
    }
    /*Request a file name, if this file exist in server, client will receive the data from the file*/
    while (1)
    {
        /*Request file name*/
        printf("Please enter the file: ");
        scanf("%s", file_name);
        /*Send the file name to server*/
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
        /*Read the TCP socket, if there are data or message from server, print out to terminal*/
        /*If the number of characters read from socket is 0, this means the server has closed*/
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