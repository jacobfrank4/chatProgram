/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: main.cpp
--
-- PROGRAM: chat_server
--
-- FUNCTIONS:
--  int main(int argc, char **argv)
--
-- DATE: Feb 22, 2017
--
-- REVISIONS: 
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- NOTES: Main entry of this program. This program wait for the TCP connection of clients.
--  After the connection established, it receives messages from clients and broadcst the mssages to the other clients.
-- Thus, the clients can exchange messages and chat via this program.
----------------------------------------------------------------------------------------------------------------------*/
#include "server.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: main
--
-- DATE: March 17, 2017
--
-- DESIGNER: 
--
-- PROGRAMMER: 
--
-- INTERFACE: int main(int argc, char **argv)
--           
-- RETURNS: int
--
-- NOTES:
--  Main function of this program. Recevies port number as a command argument and initializes socket.
----------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    int nready;
    int port;
    char buf[BUFLEN];
    fd_set rset, allset;

    switch (argc)
    {
    case 1:
        port = SERVER_TCP_PORT; // Use the default port
        break;
    case 2:
        port = atoi(argv[1]); // Get user specified port
        break;
    default:
        fprintf(stderr, "Usage: %s [port]\n", argv[0]);
        exit(1);
    }

    Server server(port);

    FD_ZERO(&allset);
    FD_SET(server.getListenSocket(), &allset);

    while (TRUE)
    {
        rset = allset; // structure assignment
        nready = select(server.getMaxfd() + 1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(server.getListenSocket(), &rset)) // new client connection
        {
            int new_sd = server.acceptClient();
            if(new_sd == -1)
                SystemFatal("accept error");

            server.addNewClient(new_sd);
            
            FD_SET(new_sd, &allset); // add new descriptor to set

            if (--nready <= 0)
                continue; // no more readable descriptors
        }

        for(auto sockfd : server.getClientSockets()) // check all clients for data
        {
            if (FD_ISSET(sockfd, &rset))
            {
                if(!server.recv(buf, sockfd)) {
                    server.closeConnection(sockfd);
                    FD_CLR(sockfd, &allset);
                }
                else
                    server.decodeMessage(sockfd, std::string(buf));

                if (--nready <= 0)
                    break; // no more readable descriptors
            }
        }
    }
    free(buf);
    return (0);
}
