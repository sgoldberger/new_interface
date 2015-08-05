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
    QPushButton* move;
    QPushButton* cancel;
    void reset();
private:
    QFont font1;
    QLabel* title;
    QLabel* depth;
private slots:
signals:


};

#endif // WINDOW3_H
