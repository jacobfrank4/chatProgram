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
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(870, 405);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sendTextEdit = new QTextEdit(centralWidget);
        sendTextEdit->setObjectName(QStringLiteral("sendTextEdit"));
        sendTextEdit->setGeometry(QRect(150, 310, 601, 31));
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(760, 310, 80, 30));
        ipAddress = new QLineEdit(centralWidget);
        ipAddress->setObjectName(QStringLiteral("ipAddress"));
        ipAddress->setGeometry(QRect(20, 230, 113, 25));
        portNumber = new QLineEdit(centralWidget);
        portNumber->setObjectName(QStringLiteral("portNumber"));
        portNumber->setGeometry(QRect(20, 260, 113, 25));
        chatTextEdit = new QTextEdit(centralWidget);
        chatTextEdit->setObjectName(QStringLiteral("chatTextEdit"));
        chatTextEdit->setGeometry(QRect(150, 10, 701, 280));
        chatTextEdit->setReadOnly(true);
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(20, 290, 80, 25));
        userListLabel = new QLabel(centralWidget);
        userListLabel->setObjectName(QStringLiteral("userListLabel"));
        userListLabel->setGeometry(QRect(20, 10, 54, 17));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 30, 111, 180));
        textEdit->setReadOnly(true);
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
