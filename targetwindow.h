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
    void refresh();
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
signals:
    void sendTarget(int num);

};

#endif // WINDOW2_H
