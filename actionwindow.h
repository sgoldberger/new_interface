#ifndef WINDOW3_H
#define WINDOW3_H

#include <QWidget>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>
#include <QPalette>

#include "igtlOSUtil.h"
#include "igtlClientSocket.h"
#include "igtlStatusMessage.h"

class actionWindow: public QWidget
{
    Q_OBJECT
public:
    actionWindow(QWidget *parent = 0);
    void displayDepth(std::string depth);
    void displayTarget(int num);
    QPushButton* back;
    QPushButton* move;
    QPushButton* cancel;
    QLabel* tarCancel;
private:
    QFont font1;
    QLabel* title;
    QLabel* depth;
private slots:
    //void recSocket(igtl::ClientSocket::Pointer sckt, igtl::StatusMessage::Pointer msg, int num, std::string depthVal);
    //void cancelled();
    //void moveSent();
    //void reset();
signals:
    //void moveToWindow2();

};

#endif // WINDOW3_H
