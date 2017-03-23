/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: server.h 
--
-- PROGRAM: chat_server
--
-- FUNCTIONS:
--
-- DATE: Feb 22, 2017
--
-- REVISIONS: 
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- NOTES: This header file contains the declaration of Server class.
----------------------------------------------------------------------------------------------------------------------*/
#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define SERVER_TCP_PORT 7000 // Default port
#define BUFLEN 1024           //Buffer length
#define TRUE 1
#define LISTENQ 5
#define MAXLINE 4096
#define USERNAMELEN 100

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: SystemFatal
--
-- DATE: March 17, 2017
--
-- DESIGNER: 
--
-- PROGRAMMER: 
--
-- INTERFACE: static void SystemFatal(const char *message)
--                          @message - error message
--           
-- RETURNS: void
--
-- NOTES:
-- Called when fatal error occurs. Prints out the error message and exit the program.
----------------------------------------------------------------------------------------------------------------------*/
static void SystemFatal(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

class Server {
public:
    Server(int port = SERVER_TCP_PORT);
    int acceptClient();
    void addNewClient(int);
    void sendUserList(int);
    void broadcast(int sockfd, std::string&);
    bool recv(char*, int);
    void closeConnection(int);
    void decodeMessage(int, std::string);

    int getListenSocket() const;
    const std::vector<int>& getClientSockets() const;
    int getMaxfd() const;

private:
    int listen_sd, maxfd;
    std::vector<int> client_list;
    std::map<int, std::string> client_names;
    struct sockaddr_in server, client_addr;
};
#endif