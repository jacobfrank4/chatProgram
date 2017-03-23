#include "client.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Client
--
-- DATE: March 18, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: Client::Client()
--
-- NOTES:
-- Constructor of Client Class.
----------------------------------------------------------------------------------------------------------------------*/
Client::Client()
{
    boolConnected = false;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: initSocket
--
-- DATE: March 18, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: bool Client::initSocket(QString _ipAddr, QString _port)
--                      QString _ipAddr: the string data of ip address for the server
--                      QString _port: the string data of port number for the server
--
-- RETURNS: true on successfull creating socket
--
-- NOTES:
-- Creates a TCP socket with the passed ip address and port number to establish TCP connection to server.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::initSocket(QString _ipAddr, QString _port){
     int port;
     struct hostent *hp;
     struct sockaddr_in server;
     bool convertOK;

     port = _port.toInt(&convertOK);

     if(!convertOK)
         return false;

     // Create the socket
     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
     {
         perror("Cannot create socket");
         exit(1);
     }

     bzero((char *)&server, sizeof(struct sockaddr_in));
     server.sin_family = AF_INET;
     server.sin_port = htons(port);

     if ((hp = gethostbyname(_ipAddr.toStdString().c_str())) == NULL)
     {
         fprintf(stderr, "Unknown server address\n");
         return false;
     }

     bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

     // Connecting to the server
     if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
     {
         fprintf(stderr, "Can't connect to server\n");
         perror("connect");
         return false;
     }
     printf("Connected:    Server Name: %s\n", hp->h_name);
     boolConnected = true;

     return boolConnected;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: sendMessage
--
-- DATE: March 18, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: bool Client::sendMessage(QString message)
--                      QString message : the string data to be sent to server.
--
-- RETURNS: true on successfull sending message
--
-- NOTES:
-- A wrapper function to send data to server via the socket.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::sendMessage(QString message) {
    if(send(sock, message.toStdString().c_str(), BUFLEN, 0)<0)
        return false;
    return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: changeUserName
--
-- DATE: March 18, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: bool Client::changeUserName(QString _name)
--                      QString _name: a string data of username to be sent to the server
--
-- RETURNS: true on successfull creating socket
--
-- NOTES:
-- Called when the tcp connection to the server is established. Sends the passed user name to the server
-- to inform and update the other user's user list
----------------------------------------------------------------------------------------------------------------------*/
bool Client::changeUserName(QString _name) {
    username = _name;
    QString message = '1' + username;
    sendMessage(message);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: recvMessage(char* buffer)
--
-- DATE: March 18, 2017
--
-- DESIGNER: Jacob Frank
--
-- PROGRAMMER: Jacob Frank
--
-- INTERFACE: bool recvMessage(char* buffer)
--                      char* buffer: buffer to store the bytes read from the socket
--
-- RETURNS: true on successfull read
--
-- NOTES:
-- When function is called, bytes are read from the socket equal to the defined BUFLEN size and stored into
-- the buffer passed into the function.
----------------------------------------------------------------------------------------------------------------------*/
bool Client::recvMessage(char* buffer){
    int n = 0;
    int bytes_to_read = BUFLEN;
    while ((n = recv(sock, buffer, bytes_to_read, 0)) < BUFLEN)
    {
        buffer += n;
        bytes_to_read -= n;
    }
    return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getUserName
--
-- DATE: March 18, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: QString Client::getUserName()
--
-- RETURNS: the string data of username
--
-- NOTES:
-- Returns the username
----------------------------------------------------------------------------------------------------------------------*/
QString Client::getUserName() {
    return username;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: isConnected
--
-- DATE: March 18, 2017
--
-- DESIGNER: Terry Kang
--
-- PROGRAMMER: Terry Kang
--
-- INTERFACE: bool Client::isConnected()
--
-- RETURNS: true if connected to the server
--
-- NOTES:
-- Return true if connected to the server or false if not connected
----------------------------------------------------------------------------------------------------------------------*/
bool Client::isConnected(){
    return boolConnected;
}
