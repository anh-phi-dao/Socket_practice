#include "multilple_client_server.h"
#include "socket.h"
#include <sys/poll.h>

char buff[1024];
char message[1024];
int val_write;
int val_read;
/*These structs are used to control multiple clients*/
struct pollfd read_fdps[MAXIMUM_CLIENT];
struct pollfd connect_fdp;
int ret;
int new_fd;

int main()
{
    /*create an TCP server using IPv4 address and defined maximum client*/
    if (create_TCP_IPv4_server(&server, PORT, MAXIMUM_CLIENT, &server_fd, &len) == ERROR)
    {
        return -1;
    }

    printf("Ready to connect \n");

    /*Assign POLLIN event for server fd*/
    /*This means when server receive a connect request from client, poll() will return >0 result*/
    connect_fdp.fd = server_fd;
    connect_fdp.events = POLLIN;
    /*Assign POLLIN event for clients fds*/
    /*This means when a client sends a message, the client is ready to read and poll() will return >o result*/
    for (int i = 0; i < MAXIMUM_CLIENT; i++)
    {
        read_fdps[i].events = POLLIN;
    }

    /*Clients can request to read a file name or request to close the server*/
    /*We need to check client's request*/
    int message_handling = 0;

    while (1)
    {
        /*Reset the buff and message to store the file name*/
        for (int i = 0; i < 1024; i++)
        {
            buff[i] = 0;
            message[i] = 0;
        }

        /*Wait 0.1 seconds for new connection*/
        ret = poll(&connect_fdp, 1, 100);

        /*If there are new connection, accept the client's connection request*/
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

        /*check each client, if there is any client is ready for the server to get the request*/
        /*then check the the requested file, if there is no matched file, send back a message to the*/
        /*client that server can not find the file*/
        /*If the requested file is matched with one file in the server, send the file's data back to the clients*/
        /*If the client request to close the server, go to the close block*/
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
        /*This is the close block*/
        /*This block will handle the closing request of the clients and break out of the infinity loop*/
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