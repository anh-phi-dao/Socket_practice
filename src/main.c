#include "multilple_client_server.h"
#include "socket.h"
#include <sys/poll.h>

char buff[1024];
char message[1024];
int val_write;
int val_read;

struct pollfd read_fdps[MAXIMUM_CLIENT];
struct pollfd connect_fdp;
int ret;
int new_fd;

int main()
{

    if (create_TCP_IPv4_server(&server, PORT, MAXIMUM_CLIENT, &server_fd, &len) == ERROR)
    {
        return -1;
    }
    printf("Ready to connect \n");

    connect_fdp.fd = server_fd;
    connect_fdp.events = POLLIN;

    for (int i = 0; i < MAXIMUM_CLIENT; i++)
    {
        read_fdps[i].events = POLLIN;
    }

    /*check the close condition*/
    int message_handling = 0;
    while (1)
    {
        for (int i = 0; i < 1024; i++)
        {
            buff[i] = 0;
        }

        ret = poll(&connect_fdp, 1, 0.1);

        if (ret > 0)
        {
            if ((connect_fdp.revents & POLLIN) == POLLIN)
            {
                if (accept_client_connection(&server, &server_fd, &new_fd, &len) == ERROR)
                {
                    printf("Connection to this client has failed\n");
                }

                for (int i = 0; i < MAXIMUM_CLIENT; i++)
                {
                    if (client_fd[i] == 0)
                    {
                        client_fd[i] = new_fd;
                        read_fdps[i].fd = new_fd;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < MAXIMUM_CLIENT; i++)
        {
            if (read_fdps[i].fd > 2)
            {
                ret = poll(read_fdps + i, 1, 1);
                if (ret > 0)
                {
                    message_handling = handling_message_for_multiple_clients(read_fdps + i, client_fd + i, message);
                    if (message_handling == FIND_FILE)
                    {
                        find_file_following_client_request(message, buff, client_fd + i);
                    }
                    break;
                }
            }
        }

        if (message_handling == CLOSE_MESSAGE)
        {
            for (int i = 0; i < MAXIMUM_CLIENT; i++)
            {
                if (client_fd[i] > 0)
                {
                    writen(client_fd[i], "Closing connect from server\n", 29);
                    close(client_fd[i]);
                    client_fd[i] = 0;
                }
            }
            break;
        }
    }

    printf("Closing the server\n");
    /*Close the server socket*/
    close(server_fd);

    return 0;
}