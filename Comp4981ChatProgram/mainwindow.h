#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
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

    void receiveThread();

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();

    void on_usernameLineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_clicked();

    void on_exportChatButton_clicked();

private:
    Ui::MainWindow *ui;
    Client client;
};

#endif // MAINWINDOW_H
