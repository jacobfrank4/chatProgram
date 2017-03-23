#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->usernameLineEdit->setText(DEFAULT_USERNAME);
    //ui->ipAddress->setText("96.49.228.48");
    ui->ipAddress->setText("192.168.0.200");
    ui->portNumber->setText("7000");
    ui->sendTextEdit->installEventFilter(this);  //Allows for the monitoring of the return key for sending messages
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
-- FUNCTION: eventFilter
--
-- DATE: March 21, 2017
--
-- DESIGNER: Jacob Frank
--
-- PROGRAMMER: Jacob Frank
--
-- INTERFACE: bool eventFilter(QObject *object, QEvent *event)
--                      QObject *object:
--                      QEvent *event:
--
-- RETURNS: Returns true on return key pressed, otherwise false
--
-- NOTES:
-- Function filters events that occur in the Text Edit box for sending messages to the other clients.
-- When a return key is detected, the function checks to see if the shift key is also depressed.
-- If the shift key is depressed along with the enter key, a new line character is inserted as normal.
-- If only the enter key is pressed, then the on_sendbutton_clicked() method is called which sends the message to
-- the server for transmission to all the clients.
----------------------------------------------------------------------------------------------------------------------*/
bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->sendTextEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return && !(keyEvent->modifiers() & Qt::ShiftModifier)) {
            on_sendButton_clicked();
            return true;
        }
    }
    return false;
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: on_sendButton_clicked
--
-- DATE: March 18, 2017
--
-- REVISIONS:
--      JF: March 21, 2017: Added functionality so scrollbar focus is always at bottom
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void updateChatBox(QString message)
--                  QString message: Text data to be written to the chat area of the GUI
--
-- RETURNS: void.
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void MainWindow::updateChatBox(QString message) {
    ui->chatTextEdit->append(message);
    ui->chatTextEdit->verticalScrollBar()->setValue(ui->chatTextEdit->verticalScrollBar()->maximum());
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
