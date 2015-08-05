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
    QPushButton* viewTargetsButton;
    char* getIp();
    int getPort();
private:
    QLineEdit* ipAdd;
    QLineEdit* port;
    int* portNum;
    char* hostname;
    bool inputIP;
    bool inputPort;
private slots:
    void readIp();
    void readPort();
signals:

};

#endif // CONNECTWINDOW_H
