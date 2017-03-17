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

void MainWindow::on_connectButton_clicked()
{
    if(client.isConnected())
        return;

    QString ipAddr = ui->ipAddress->text();
    QString port = ui->portNumber->text();

    if(ipAddr.length() < 1 || port.length() < 1)
        return;

    if(client.initSocket(ipAddr, port))
        client.changeUserName("Terry");
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
