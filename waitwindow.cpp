#include "waitwindow.h"
#include <QDebug>

waitWindow::waitWindow(QWidget* parent):
    QWidget(parent)
{
    //set window
    QSize screenSize = parent->size();
    int screenW = screenSize.width();
    int screenH = screenSize.height();
    //setGeometry(0,0,screenW,screenH);
    QPalette pal = this -> palette();
    pal.setColor(QPalette::Window, Qt::black);
    this->setPalette(pal);

    QFont font("", .04 *screenH, 25, false);
    font.setFamily(font.defaultFamily());

    cancel = new QPushButton("Cancel", this);
    cancel -> setGeometry(screenW/100,screenH/50,screenW/5,screenH/6);
    cancel -> setFont(font);

    title = new QLabel("Waiting for target selection",this, 0);
    QPalette textPal = title->palette();
    textPal.setColor(QPalette::WindowText, Qt::gray);
    title -> setGeometry((3*screenW)/10,(41*screenH/600), screenW/2, screenH/15 );
    title ->setFont(font);
    title -> setPalette(textPal);
}



