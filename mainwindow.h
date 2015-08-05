#ifndef WINDOW1_H
#define WINDOW1_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QDesktopWidget>
#include <QApplication>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlStatusMessage.h"

#include "connectwindow.h"
#include "waitwindow.h"
#include "targetwindow.h"
#include "actionwindow.h"

class mainwindow: public QWidget
{
    Q_OBJECT
public:
    mainwindow(QWidget *parent = 0);
private:
    QStackedWidget* stack;
    connectWindow* connectScreen;
    waitWindow* waitScreen;
    targetWindow* targetScreen;
    actionWindow* actionScreen;
    igtl::ClientSocket::Pointer socket;
    igtl::StatusMessage::Pointer statMsg;
    igtl::StatusMessage::Pointer recMsg;
    int handshake();
    void sendMessage(const char* msg);
    const char* receiveMessage();
    void receiveNumberOfTargets();
    std::string depth;
private slots:
    void connectToServer();
    void disconnectFromServer();
    void waitCancelled();
    void targetScreenCancelled();
    void slotSendTarget(int num);
    void slotSendMove();
    void slotSendCancel();
    void actionScreenCancelled();
signals:

};

#endif // WINDOW1_H
