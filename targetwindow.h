#ifndef WINDOW2_H
#define WINDOW2_H

#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QDesktopWidget>
#include <QLabel>
#include <QApplication>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlStatusMessage.h"

class targetWindow: public QWidget

{
    Q_OBJECT
public:
    targetWindow(QWidget *parent = 0);
    void buildTargets(int num);
    QPushButton* back;
private:
    QPushButton* target1;
    QPushButton* target2;
    QPushButton* target3;
    QPushButton* target4;
    QPushButton* target5;
    QPushButton* target6;
    QPushButton* target7;
    QPushButton* target8;
    QLabel* title;
    QSignalMapper* sigMapper;
private slots:
    void targetSel(int num);
    //void recTar(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer status, int numTar);
    void refresh();
    //void moveSent();
signals:
    //void moveToWindow1();
    //void moveToWindow3();
    //void sendSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg, int num, std::string depth);
    void sendTarget(int num);

};

#endif // WINDOW2_H
