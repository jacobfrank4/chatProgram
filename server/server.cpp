/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: server.cpp
--
-- PROGRAM: chat_server
--
-- FUNCTIONS:
--  Server(int port = SERVER_TCP_PORT);
--  int acceptClient();
--  void addNewClient(int);
--  void sendUserList(int);
--  void broadcast(int sockfd, std::string&);
--  bool recv(char*, int);
--  void closeConnection(int);
--  void decodeMessage(int, std::string);
--  int getListenSocket() const;
--  const std::vector<int>& getClientSockets() const;
--  int getMaxfd() const;
--
-- DATE: Feb 22, 2017
--
-- REVISIONS: 
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- NOTES: This file contains the definition of functions of Session class.
----------------------------------------------------------------------------------------------------------------------*/
#include "server.h"


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Server
--
-- DATE: March 18, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: Server::Server(int port)
--                  @ port - socket port number
-- RETURNS:
--
-- NOTES:
-- Constructor of Server class. initilizes sockets and start to listen.
----------------------------------------------------------------------------------------------------------------------*/
Server::Server(int port) {
    // Create a stream socket
    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        SystemFatal("Cannot Create Socket!");

    // set SO_REUSEADDR so port can be resused imemediately after exit, i.e., after CTRL-c
    int arg = 1;
    if (setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1)
        SystemFatal("setsockopt");

    // Bind an address to the socket
    bzero((char *)&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

    if (bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        SystemFatal("bind error");

    // Listen for connections
    // queue up to LISTENQ connect requests
    listen(listen_sd, LISTENQ);

    maxfd = listen_sd; // initialize

}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: acceptClient
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: int Server::acceptClient(){
--                  
-- RETURNS: int - new socket value
--
-- NOTES:
-- Wrapper function for accept a new connection.
----------------------------------------------------------------------------------------------------------------------*/
int Server::acceptClient(){
    int client_len;
    int new_sd;

    client_len = sizeof(client_addr);

    new_sd = accept(listen_sd, (struct sockaddr *)&client_addr, (socklen_t *)&client_len);

    return new_sd;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: addNewClient
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: void Server::addNewClient(int new_sd)
--                  @new_sd - new socket value
-- RETURNS: void
--
-- NOTES:
-- Add new socket connection to a vector array.
----------------------------------------------------------------------------------------------------------------------*/
void Server::addNewClient(int new_sd){

    printf(" Remote Address:  %s\n", inet_ntoa(client_addr.sin_addr));

    client_list.push_back(new_sd);
        
    if (client_list.size() == FD_SETSIZE)
    {
        printf("Too many clients\n");
        exit(1);
    }

    if (new_sd > maxfd)
        maxfd = new_sd; // for select

    sendUserList(new_sd);

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendUserList
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: void Server::sendUserList(int sockfd)
--                  @socfd - socket value of new client
-- RETURNS: void
--
-- NOTES:
--  Sends the list of connected users to new client.
----------------------------------------------------------------------------------------------------------------------*/
void Server::sendUserList(int sockfd) {
    std::string list("2");
    for (const auto& c : client_list) // check all clients for data
    {
        if (c != sockfd) {
            list += client_names[c] + ":";
        }
    }
    write(sockfd, list.c_str(), BUFLEN);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: broadcast
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: void Server::broadcast(int sockfd, std::string &message)
--                  @sockfd - the sender's socket value
--                  @message - message to broadcast
-- RETURNS: void
--
-- NOTES:
--  Broadcast the passed message to all connected client except the sender
----------------------------------------------------------------------------------------------------------------------*/
void Server::broadcast(int sockfd, std::string &message) {
    for (const auto& c : client_list)  // check all clients for data
    {
        if (c != sockfd) {
            write(c, message.c_str(), BUFLEN); // echo to client
        }
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: recv
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: bool Server::recv(char *buf, int sockfd)
--                  @buf - the buffer for receiving data
--                  @sockfd - the socket to receive.
-- RETURNS: bool
--
-- NOTES:
--  Receive message from the passed socket. if no message, it close the connection.
----------------------------------------------------------------------------------------------------------------------*/
bool Server::recv(char *buf, int sockfd){
    char *bp = buf;
    int bytes_to_read = BUFLEN;
    int n;
    while ((n = read(sockfd, bp, bytes_to_read)) > 0)
    {
        bp += n;
        bytes_to_read -= n;
    }

    if (bytes_to_read == BUFLEN) // connection closed by client
    {
        return false;
    }else{
        return true;
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: closeConnection
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: void Server::closeConnection(int sockfd)
--                  @sockfd - the socket to close
-- RETURNS: void
--
-- NOTES:
--  Close the connection of the passed socket and broadcast to all other clients.
----------------------------------------------------------------------------------------------------------------------*/
void Server::closeConnection(int sockfd){
    printf(" Remote Address:  %s closed connection\n", inet_ntoa(client_addr.sin_addr));
    auto it = std::find(client_list.begin(), client_list.end(), sockfd);
    if(it != client_list.end()){

        close(sockfd);
        std::string message = "------------- [" + client_names[sockfd] + "] left -------------";
        printf("%s\n", message.c_str());
        broadcast(sockfd, message);
        message = "3" + client_names[sockfd];
        broadcast(sockfd, message);
        client_list.erase(it);
        client_names.erase(sockfd);
    }


}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: decodeMessage
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: void Server::decodeMessage(int sockfd, std::string message)
--                  @sockfd - the socket of sender
--                  @message - the received message
-- RETURNS: void
--
-- NOTES:
--  Reads first character of message and handles it.
----------------------------------------------------------------------------------------------------------------------*/
void Server::decodeMessage(int sockfd, std::string message) {
    if(message[0] == '1'){ // user joined and sent new user name
        client_names[sockfd] = message.substr(1);
        printf("------------- [%s] joined -------------\n", client_names[sockfd].c_str());
        broadcast(sockfd, message);
    }
    else{ // regular chat message
        printf("%s\n", message.substr(1).c_str());
        broadcast(sockfd, message);
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getListenSocket
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: int Server::getListenSocket() const
--                  
-- RETURNS: int - listen socket
--
-- NOTES:
--  Returns the listen socket
----------------------------------------------------------------------------------------------------------------------*/
int Server::getListenSocket() const{
    return listen_sd;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getClientSockets
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: const std::vector<int>& Server::getClientSockets() const
--                  
-- RETURNS: const std::vector<int>& - vector array of client sockets
--
-- NOTES:
--  Returns the list of clients' sockets
----------------------------------------------------------------------------------------------------------------------*/
const std::vector<int>& Server::getClientSockets() const{
    return client_list;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getMaxfd
--
-- DATE: March 22, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: int Server::getMaxfd() const
--                  
-- RETURNS: int - maxfd
--
-- NOTES:
--  Returns maxfd
----------------------------------------------------------------------------------------------------------------------*/
int Server::getMaxfd() const{
    return maxfd;
}
