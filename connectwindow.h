#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QDesktopWidget>
#include <QApplication>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlStatusMessage.h"


class connectWindow: public QWidget
{
    Q_OBJECT
public:
    connectWindow(QWidget *parent = 0);
    igtl::ClientSocket::Pointer socket;
    igtl::StatusMessage::Pointer statMsg;
    QPushButton* connectButton;
    QPushButton* disconnectButton;
private:
    //QLineEdit* ipAdd;
    //QLineEdit* port;
    //const QRect screenSize;
    //int portNum;
    //char* hostname;
    //int handshake();
private slots:
    //void getIp();
    //void getPort();
   // void connectToServer();
    //void disconnectServer();
signals:
    //void connectedToServer();
    //void socketCreated(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer status);
    //void refresh();

};

#endif // CONNECTWINDOW_H
