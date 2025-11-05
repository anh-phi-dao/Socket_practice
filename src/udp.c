#include "server_udp.h"

char data[1024];
char buff[1024];
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

    create_UDP_IPv4_server(&server, PORT, &server_udp_fd, &len);

    /*in client, kernel will bind random port*/
    create_UDP_IPv4_client_address(&client, "192.168.27.167", 8800);
    int i = 0;
    do
    {
        if (i < 10)
        {
            val_read = recvfrom(server_udp_fd, buff, 1024, 0, (struct sockaddr *)&client, &len);
            i++;
        }
        else
        {
            printf("Failed on receiving from client\nEscape now\n");
            return -1;
        }

    } while (val_read <= 0);

    val_write = sendto(server_udp_fd, data, 1024, 0, (struct sockaddr *)&client, len);

    printf("Bytes have been sent:%d\n", val_write);
    i = 0;
    do
    {
        if (i < 10)
        {
            val_read = recvfrom(server_udp_fd, buff, 1024, 0, (struct sockaddr *)&client, &len);
            i++;
        }
        else
        {
            printf("Received 0 byte\n");
            goto out;
        }

    } while (val_read == 0);

    printf("Received %d bytes\n%s\n", val_read, buff);
out:
    close(server_udp_fd);
    return 0;
}