#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextBlock>
#include <QScrollBar>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateChatBox(QString message);
    void decodeMessage(QString message);
    void addUser(QString username);
    void updateUserList(QString userlist);
    void receiveThread();
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();

    void on_exportChatButton_clicked();

    void removeUser(QString username);

signals:
    void userLeft(QString username);

private:
    Ui::MainWindow *ui;
    Client client;
};

#endif // MAINWINDOW_H
