#ifndef WAITWINDOW_H
#define WAITWINDOW_H

#include <QWidget>
#include <QFont>
#include <QLabel>
#include <QDesktopWidget>
#include <QApplication>
#include <QPushButton>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlStatusMessage.h"

class waitWindow: public QWidget
{
    Q_OBJECT
public:
    waitWindow(QWidget* parent = 0);
    void setSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg);
    QPushButton* cancel;
    int numTar;
private:
    QLabel* title;
    igtl::ClientSocket::Pointer socket;
    bool noTargets;
    igtl::StatusMessage::Pointer statMsg;
    const char* sNumTar;
private slots:
    //void recSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer statMsg);
    //void sendTarget(int num);
signals:
    //void sendNumTar(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg, int numTar);
    //void backToWindow1();
    //void hideW1();
    void receivedTargets();
    void backToConnectWindow();
};

#endif // WAITWINDOW_H
