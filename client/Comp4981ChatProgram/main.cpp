/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: main.cpp
--
-- PROGRAM: chatProgram
--
-- DATE: March 15, 2017
--
-- DESIGNER: Terry Kang, Jacob Frank
--
-- PROGRAMMER: Terry Kang, Jacob Frank
--
-- NOTES:
-- This program is a client program for online chat via TCP connection on QT.
--
-- This program gets the ip address and port number from user via text fields on QT winodws
-- and then creates a TCP connection to the server.
-- After the connection is established, this program waits for the user's message input.
-- When user enters a message, the message is sent to the server via the tcp connection.
-- Also, this program read messages from the server via the connection and display it on the window.
----------------------------------------------------------------------------------------------------------------------*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
