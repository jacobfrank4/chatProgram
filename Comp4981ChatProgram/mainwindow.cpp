#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->usernameLineEdit->setText(DEFAULT_USERNAME);
    ui->ipAddress->setText("96.49.228.48");
    ui->portNumber->setText("7000");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_connectButton_clicked
--
-- DATE: March 15, 2017
--
-- REVISIONS:
--      JF: March 18, 2017: Added functionality to get the users name from a text field in the UI
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void on_connectButton_clicked()
--
-- RETURNS: void.
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_connectButton_clicked()
{
    if(client.isConnected())
        return;

    QString ipAddr = ui->ipAddress->text();
    QString port = ui->portNumber->text();
    QString username = ui->usernameLineEdit->text().trimmed();

    if (username.isEmpty()) {
        username = DEFAULT_USERNAME;
    }

    if(ipAddr.length() < 1 || port.length() < 1)
        return;

    if(client.initSocket(ipAddr, port)) {
        client.changeUserName(username);
        ui->usernameLineEdit->setReadOnly(true); //Stops user from changing their name after connecting to the server
        std::thread receivingThread(&MainWindow::receiveThread, this);
        receivingThread.detach();
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: receiveThread
--
-- DATE: March 18, 2017
--
-- DESIGNER: Jacob Frank
--
-- PROGRAMMER: Jacob Frank
--
-- INTERFACE: void receiveThread()
--
-- RETURNS: void.
--
-- NOTES:
-- Function called upon successfull connection to the server.
-- Starts an infinite reading loop that continuosly monitors the socket for messages to receive.
-- Upon successful read of information from socket, helper function is called to update the chat window.
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::receiveThread() {
    char *buf;
    buf = (char *)malloc(sizeof(char) * BUFLEN);
    while (1) {
        client.recvMessage(buf);
        updateChatBox(buf);
    }
    free(buf);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_sendButton_clicked
--
-- DATE: March 18, 2017
--
-- REVISIONS:
--      JF: March 18, 2017:Removed new line character added to end of
--          message to prevent vertical gaps between messages
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: on_sendButton_clicked()
--
-- RETURNS: void.
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_sendButton_clicked()
{
    if(!client.isConnected())
        return;
    QString message = ui->sendTextEdit->toPlainText();

    if(message.length() < 1)
        return;

    client.sendMessage("1[" + client.getUserName() + "] : " + message);
    updateChatBox("[me] : " + message);
    ui->sendTextEdit->setText("");

}

void MainWindow::updateChatBox(QString message) {
    ui->chatTextEdit->append(message);
}
