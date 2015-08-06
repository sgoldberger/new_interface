#include "connectwindow.h"
#include <QDebug>

connectWindow::connectWindow(QWidget* parent):
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

    QFont font("", .045 *screenH, 25, false);
    font.setFamily(font.defaultFamily());

    QFont font2("", .035 *screenH, 25, false);
    font2.setFamily(font2.defaultFamily());

    //build input lines

    ipAdd = new QLineEdit(this);
    ipAdd -> setGeometry(.25 * screenW, .1 * screenH, .5 * screenW, .125 * screenH);
    ipAdd -> setPlaceholderText("Enter IP Address");
    ipAdd -> setFont (font);

    port = new QLineEdit(this);
    port -> setGeometry(.25*screenW, .25 * screenH, .5 * screenW,.125 * screenH);
    port -> setPlaceholderText("Enter Port Number");
    port -> setFont(font);


    //build buttons
    connectButton = new QPushButton("Connect to server", this);
    //connectButton -> setGeometry(.25 * screenW, .2* screenH, .5 * screenW, .3 * screenH); no input lines
    connectButton -> setGeometry(.25*screenW, .415*screenH, .5*screenW, .2*screenH);
    connectButton -> setFont(font);
    connectButton -> setEnabled(false);

    disconnectButton = new QPushButton("Disconnect", this);
    //disconnectButton -> setGeometry(.25 * screenW, .5 * screenH, .5 * screenW, .125 * screenH); no input lines
    disconnectButton -> setGeometry(.25*screenW, .625*screenH, .5*screenW, .125*screenH);
    disconnectButton -> setFont(font);
    disconnectButton -> setEnabled(false);

    viewTargetsButton = new QPushButton("View targets", this);
    viewTargetsButton -> setGeometry((3*screenW)/4, (19*screenH)/24, screenW/5,screenH/6);
    viewTargetsButton -> setFont(font2);
    viewTargetsButton -> setVisible(false);

    connect(ipAdd, SIGNAL(editingFinished()), this, SLOT(readIp()));
    connect(port, SIGNAL (editingFinished()), this, SLOT(readPort()));

    bool inputIP = false;
    bool inputPort = false;

}


void connectWindow::readIp()
{
    QString input = ipAdd->text();
    QByteArray ba = input.toLocal8Bit();
    hostname = new char[20];
    std::strcpy(hostname, ba.data());
    if(strcmp(hostname, "") !=0)
    {
        inputIP = true;
    }

    if (inputIP && inputPort)
    {
        connectButton -> setEnabled(true);
    }

}

void connectWindow::readPort()
{
    QString input = port->text();
    portNum = new int;
    *portNum = input.toInt();

    inputPort = true;
    if (inputIP && inputPort)
    {
        connectButton -> setEnabled(true);
    }
}

char* connectWindow::getIp()
{
    return hostname;
}

int connectWindow::getPort()
{
    return *portNum;
}

