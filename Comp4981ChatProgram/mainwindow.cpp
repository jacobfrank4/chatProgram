#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->usernameLineEdit->setText(DEFAULT_USERNAME);
    ui->ipAddress->setText("96.49.228.48");
    //ui->ipAddress->setText("192.168.0.200");
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
--      JF: March 18, 2017: Added connection response to inform user that connection to server was established
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
        updateChatBox("------------- Connected -------------");
        std::thread receivingThread(&MainWindow::receiveThread, this);
        receivingThread.detach();
        connect(this, SIGNAL(userLeft(QString)), this, SLOT(removeUser(QString)));
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
        decodeMessage(buf);
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
-- INTERFACE: void on_sendButton_clicked()
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

    client.sendMessage("0[" + client.getUserName() + "] : " + message);
    updateChatBox("[me] : " + message);
    ui->sendTextEdit->setText("");

}

void MainWindow::updateChatBox(QString message) {
    ui->chatTextEdit->append(message);
}

void MainWindow::decodeMessage(QString message) {
    qDebug() << "decodeMessage";

    if(!message.at(0).isNumber())
        return;
    switch(message.at(0).digitValue()){
    case 1:
        addUser(message.mid(1));
        break;
    case 2:
        updateUserList(message.mid(1));
        break;
    case 3:
        emit userLeft(message.mid(1));
        break;
    default:
        updateChatBox(message.mid(1));
        break;
    }
}

void MainWindow::addUser(QString username) {
    ui->userList->append(username);
    ui->chatTextEdit->append("------------- [" + username + "] joined -------------");
}

void MainWindow::removeUser(QString username) {
    QStringList list = ui->userList->toPlainText().split("\n");
    qDebug()<<username;

    foreach (QString name, list) {
        if(name.compare(username) == 0) {
            list.removeOne(name);
            break;
        }
    }
    qDebug()<<list;
    ui->userList->setPlainText(list.join("\n"));

    ui->chatTextEdit->append("------------- [" + username + "] left -------------");
}

void MainWindow::updateUserList(QString userlist) {
    QStringList list = userlist.split(":");
    foreach (QString name, list) {
        if(name.length()>0)
            ui->userList->append(name);
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_pushButton_clicked
--
-- DATE: March 18, 2017
--
-- DESIGNER: Jacob Frank
--
-- PROGRAMMER: Jacob Frank
--
-- INTERFACE: void on_pushButton_clicked()
--
-- RETURNS: void
--
-- NOTES:
-- Called when user clicks the export chat button.
-- Creates a text file with a name specifed by the user via a dialog window
-- After user specifies file name and save location, function saves the contents of the chat window to the file
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::on_exportChatButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save File", "/home/chat.txt", "Text Files (*.txt)");
    QFile handle(filename);

    if (handle.open(QIODevice::ReadWrite)) {
        QTextStream out(&handle);

        out << ui->chatTextEdit->toPlainText(); //writes contents of chat to specified file
    }
    handle.close();
}
