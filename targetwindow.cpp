#include "targetwindow.h"
#include <QDebug>

targetWindow::targetWindow(QWidget *parent):
    QWidget(parent)
{
    //set window
    //const QRect screenSize = desktop->screenGeometry();
    int screenW = 800;
    int screenH = 600;
    setGeometry(0,0,800,600);
    setWindowTitle("Connected to Server"); //display ip add/port num?
    QPalette pal = this -> palette();
    pal.setColor(QPalette::Window, Qt::black);
    this->setPalette(pal);

    QFont font1("", .04 *screenH, 25, false);
    font1.setFamily(font1.defaultFamily());

    QFont font2("", .05 * screenH, 25, false);
    font2.setFamily(font2.defaultFamily());

    sigMapper = new QSignalMapper(this);

    back = new QPushButton("Go back", this);
    back -> setGeometry(screenW/100,screenH/50,screenW/5,screenH/6);
    back -> setFont(font1);

    title = new QLabel("Select target to send to robot",this, 0);
    QPalette textPal = title->palette();
    textPal.setColor(QPalette::WindowText, Qt::gray);
    title -> setGeometry(screenW/4,(41*screenH/600), (2*screenW)/3, screenH/15 );
    title ->setFont(font2);
    title -> setPalette(textPal);

    //build targets
    target1 = new QPushButton("Target 1", this);
    target1 -> setGeometry((7*screenW)/100, screenH/4, screenW/5, screenH/5);
    target1 -> setFont(font1);
    sigMapper -> setMapping(target1, int(1));
    connect(target1, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target1 -> setVisible(false);

    target2 = new QPushButton("Target 2", this);
    target2 -> setGeometry((29*screenW)/100, screenH/4, screenW/5, screenH/5);
    target2 -> setFont(font1);
    sigMapper -> setMapping(target2, int(2));
    connect(target2, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target2 -> setVisible(false);

    target3 = new QPushButton("Target 3", this);
    target3-> setGeometry((51*screenW)/100, screenH/4 ,screenW/5, screenH/5);
    target3 -> setFont(font1);
    sigMapper -> setMapping(target3, int(3));
    connect(target3, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target3 -> setVisible(false);

    target4 = new QPushButton("Target 4", this);
    target4-> setGeometry((73*screenW)/100, screenH/4, screenW/5, screenH/5);
    target4 -> setFont(font1);
    sigMapper -> setMapping(target4, int(4));
    connect(target4, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target4 -> setVisible(false);

    target5 = new QPushButton("Target 5", this);
    target5 -> setGeometry((7*screenW)/100, screenH/2, screenW/5, screenH/5);
    target5 -> setFont(font1);
    sigMapper -> setMapping(target5, int(5));
    connect(target5, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target5 -> setVisible(false);

    target6 = new QPushButton("Target 6", this);
    target6 -> setGeometry((29*screenW)/100, screenH/2, screenW/5, screenH/5);
    target6 -> setFont(font1);
    sigMapper -> setMapping(target6, int(6));
    connect(target6, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target6 ->setVisible(false);

    target7 = new QPushButton("Target 7", this);
    target7-> setGeometry((51*screenW)/100, screenH/2, screenW/5, screenH/5);
    target7 -> setFont(font1);
    sigMapper -> setMapping(target7, int(7));
    connect(target7, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target7 ->setVisible(false);

    target8 = new QPushButton("Target 8", this);
    target8-> setGeometry((73*screenW)/100, screenH/2, screenW/5, screenH/5);
    target8 ->setFont(font1);
    sigMapper -> setMapping(target8, int(8));
    connect(target8, SIGNAL(clicked()),sigMapper, SLOT(map()));
    target8 -> setVisible(false);

    //connect(back, SIGNAL (clicked()), this, SIGNAL (moveToWindow1()));
    //connect(back, SIGNAL(clicked()), this, SLOT(hide()));
    connect(sigMapper, SIGNAL(mapped(int)), this, SLOT(targetSel(int)));
    //connect(move, SIGNAL (clicked()), this, SLOT(moveSent()));

}

void targetWindow::targetSel(int num)
{
   //send target selected to slicer

    emit sendTarget(num);


}


void targetWindow::buildTargets(int num)
{
    if (num>0)
    {
        target1 -> setVisible(true);
        num--;
    }

    if (num>0)
     {
        target2 -> setVisible(true);
        num--;
     }

    if (num>0)
    {
        target3 ->setVisible(true);
        num--;
    }

    if (num>0)
    {
        target4 -> setVisible(true);
        num--;
    }

     if (num>0)
     {
        target5 ->setVisible(true);
        num--;
    }

     if (num>0)
     {
         target6 -> setVisible(true);
         num--;
     }

    if (num>0)
    {
        target7 -> setVisible(true);
        num--;
    }

    if (num>0)
    {
        target8 -> setVisible(true);
        num--;
    }

    if(num>0)
    {
       //more than 8 targets
    }

this -> show();
}

void targetWindow::refresh()
{
    //hide all buttons
    target1 ->setVisible(false);
    target2 ->setVisible(false);
    target3 ->setVisible(false);
    target4 ->setVisible(false);
    target5 ->setVisible(false);
    target6 ->setVisible(false);
    target7 ->setVisible(false);
    target8 ->setVisible(false);

}







