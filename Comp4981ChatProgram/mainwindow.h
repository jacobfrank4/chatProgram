#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();

    void on_usernameLineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    Client client;
};

#endif // MAINWINDOW_H
