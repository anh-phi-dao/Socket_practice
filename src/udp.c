#include "client_udp.h"

char data[1024];
int val_write;
int val_read;
int main()
{

    create_UDP_IPv4_client(&client_udp_fd);

    create_UDP_IPv4_server_address(&server, "192.168.27.167", PORT);

    sendto(client_udp_fd, "From client\n", 13, 0, (struct sockaddr *)&server, len);

    int i = 0;
    do
    {
        if (i < 10)
        {
            val_read = recvfrom(client_udp_fd, data, 1024, 0, (struct sockaddr *)&server, &len);
            i++;
        }
        else
        {
            printf("Received 0 byte\n");
            return -1;
        }

    } while (val_read == 0);

    printf("Received %d bytes\n%s\n", val_read, data);

    val_write = sendto(client_udp_fd, "Client has received data\n", 26, 0, (struct sockaddr *)&server, len);

    printf("Bytes have been sent:%d\n", val_write);
    close(client_udp_fd);
    return 0;
}