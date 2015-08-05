#include "actionwindow.h"
#include <QDebug>

actionWindow::actionWindow(QWidget *parent):
    QWidget(parent)
{
    //set window
    //const QRect screenSize = desktop->screenGeometry();
    int screenW = 800;
    int screenH = 600;
    setGeometry(0,0,800,600);
    QPalette pal = this -> palette();
    pal.setColor(QPalette::Window, Qt::black);
    this->setPalette(pal);

    QFont font1("", .04 *screenH, 25, false);
    font1.setFamily(font1.defaultFamily());

    title = new QLabel(this, 0);
    QPalette textPal = title->palette();
    textPal.setColor(QPalette::WindowText, Qt::gray);
    title -> setGeometry((3*screenW)/7,(41*screenH/600), screenW/2, screenH/15 );
    title ->setFont(font1);
    title -> setPalette(textPal);

    /*
    tarCancel = new QLabel("              Cancelled", this, 0);
    QPalette cancelPal = tarCancel -> palette();
    cancelPal.setColor(QPalette::WindowText, Qt::red);;
    tarCancel->setGeometry((3*screenW)/7,(41*screenH/600), screenW/2, screenH/15);
    tarCancel->setFont(font1);
    tarCancel -> setPalette(cancelPal);
    tarCancel -> setVisible(false);
    */

    depth = new QLabel("" ,this,0);
    depth -> setGeometry((18*screenW)/56,(2*screenH/15), screenW/2, screenH/15 );
    depth -> setFont(font1);
    depth -> setPalette(textPal);

    /*
    back = new QPushButton("Go back", this);
    back -> setGeometry(screenW/100, screenH/50, screenW/5, screenH/6);
    back -> setFont(font1);
    */

    move = new QPushButton("Move robot", this);
    move -> setGeometry((screenW)/10, screenH/4, (7*screenW)/20, screenH/5);
    move -> setFont(font1);

    cancel = new QPushButton("Cancel target", this);
    cancel -> setGeometry((11*screenW)/20, screenH/4, (7*screenW)/20, screenH/5);
    cancel -> setFont(font1);
}

void actionWindow::displayDepth(std::string depthVal)
{
    QString targetDepth = QString::fromStdString(depthVal);
    depth -> setText("Depth: " + targetDepth);
}

void actionWindow::displayTarget(int num)
{
    title->setText("Target " +QString::number(num));
}

void actionWindow::reset()
{
    move -> setText("Move robot");
    move -> setEnabled(true);
    cancel -> setText("Cancel target");
    cancel -> setEnabled(true);
}
