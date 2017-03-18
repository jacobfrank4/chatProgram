#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    if(client.initSocket(ipAddr, port))
        client.changeUserName(username);
}

void MainWindow::on_sendButton_clicked()
{
    if(!client.isConnected())
        return;
    QString message = ui->sendTextEdit->toPlainText();

    if(message.length() < 1)
        return;

    client.sendMessage("1[" + client.getUserName() + "] : " + message + "\n");
    updateChatBox("[me] : " + message);
    ui->sendTextEdit->setText("");

}

void MainWindow::updateChatBox(QString message) {
    ui->chatTextEdit->append(message);
}

void MainWindow::on_usernameLineEdit_cursorPositionChanged(int arg1, int arg2)
{

}
