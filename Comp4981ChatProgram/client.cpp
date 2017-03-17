#include "client.h"

Client::Client()
{
    boolConnected = false;
}

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

}
bool Client::sendMessage(QString message) {
    send(sock, message.toStdString().c_str(), BUFLEN, 0);
}

bool Client::changeUserName(QString _name) {
    username = _name;
    QString message = '0' + username;
    sendMessage(message);
}

bool Client::recvMessage(){
    int n = 0;
    int bytes_to_read = BUFLEN;
    char *buf;
    buf = (char *)malloc(sizeof(char) * BUFLEN);
    while ((n = recv(sock, buf, bytes_to_read, 0)) < BUFLEN)
    {
        buf += n;
        bytes_to_read -= n;
    }
    free(buf);

}

QString Client::getUserName() {
    return username;
}

bool Client::isConnected(){
    return boolConnected;
}
