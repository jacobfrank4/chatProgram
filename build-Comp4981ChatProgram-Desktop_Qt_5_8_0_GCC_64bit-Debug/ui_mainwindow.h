/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *sendTextEdit;
    QPushButton *sendButton;
    QLineEdit *ipAddress;
    QLineEdit *portNumber;
    QTextEdit *chatTextEdit;
    QPushButton *connectButton;
    QLabel *userListLabel;
    QTextEdit *userList;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QPushButton *exportChatButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(870, 446);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(45, 45, 48);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sendTextEdit = new QTextEdit(centralWidget);
        sendTextEdit->setObjectName(QStringLiteral("sendTextEdit"));
        sendTextEdit->setGeometry(QRect(150, 350, 601, 31));
        sendTextEdit->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(760, 350, 91, 30));
        sendButton->setStyleSheet(QLatin1String("background-color: rgb(38, 22, 77);\n"
"color: rgb(255, 255, 255);"));
        ipAddress = new QLineEdit(centralWidget);
        ipAddress->setObjectName(QStringLiteral("ipAddress"));
        ipAddress->setGeometry(QRect(20, 270, 113, 25));
        ipAddress->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        portNumber = new QLineEdit(centralWidget);
        portNumber->setObjectName(QStringLiteral("portNumber"));
        portNumber->setGeometry(QRect(20, 300, 113, 25));
        portNumber->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        chatTextEdit = new QTextEdit(centralWidget);
        chatTextEdit->setObjectName(QStringLiteral("chatTextEdit"));
        chatTextEdit->setGeometry(QRect(150, 50, 701, 280));
        chatTextEdit->setStyleSheet(QLatin1String("background-color: rgb(30, 30, 30);\n"
"color: rgb(255, 255, 255);"));
        chatTextEdit->setReadOnly(true);
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(20, 350, 80, 31));
        connectButton->setStyleSheet(QLatin1String("background-color: rgb(38, 22, 77);\n"
"color: rgb(255, 255, 255);"));
        userListLabel = new QLabel(centralWidget);
        userListLabel->setObjectName(QStringLiteral("userListLabel"));
        userListLabel->setGeometry(QRect(20, 20, 54, 21));
        userListLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        userList = new QTextEdit(centralWidget);
        userList->setObjectName(QStringLiteral("userList"));
        userList->setGeometry(QRect(20, 49, 111, 201));
        userList->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(30, 30, 30);"));
        userList->setReadOnly(true);
        usernameLabel = new QLabel(centralWidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(150, 20, 61, 21));
        usernameLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        usernameLineEdit = new QLineEdit(centralWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));
        usernameLineEdit->setGeometry(QRect(220, 20, 151, 21));
        usernameLineEdit->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        exportChatButton = new QPushButton(centralWidget);
        exportChatButton->setObjectName(QStringLiteral("exportChatButton"));
        exportChatButton->setGeometry(QRect(730, 20, 121, 25));
        exportChatButton->setStyleSheet(QLatin1String("background-color: rgb(38, 22, 77);\n"
"color: rgb(255, 255, 255);"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 870, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        sendButton->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        ipAddress->setText(QApplication::translate("MainWindow", "IP Address", Q_NULLPTR));
        portNumber->setText(QApplication::translate("MainWindow", "Port Number", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        userListLabel->setText(QApplication::translate("MainWindow", "Users", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("MainWindow", "Username:", Q_NULLPTR));
        usernameLineEdit->setText(QString());
        exportChatButton->setText(QApplication::translate("MainWindow", "Save Chat", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
