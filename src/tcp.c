#include "server.h"
#include "socket.h"

char data[1024];
int val_write;
int val_read;
int main()
{
    FILE *fileptr = fopen("test.txt", "r");
    if (fileptr == NULL)
    {
        printf("Open test.txr file doesn't success\nPlease check your file\n");
        return -1;
    }
    char num = fgetc(fileptr) - 48;
    fgetc(fileptr);
    for (int i = 0; i < num + 1; i++)
    {
        fgets(data + strlen(data), 1024, fileptr);
    }
    fclose(fileptr);
    if (create_TCP_IPv4_server(&server, PORT, MAXIMUM_CLIENT, &server_fd, &len) == ERROR)
    {
        return -1;
    }

    if (accept_client_connection(&server, &server_fd, &client_fd, &len))
    {
        return -1;
    }
    val_write = writen(client_fd, data, 1024);
    printf("Number of bytes have been seen:%u\n", val_write);
    do
    {
        val_read = readn(client_fd, data, 1024);

    } while (val_read > 0);
    printf("From client with IPv4:%s :%s", IP, data);
    close(server_fd);
}