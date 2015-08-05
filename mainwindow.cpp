#include "mainwindow.h"
#include <QDebug>

mainwindow::mainwindow(QWidget *parent):
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

    connectScreen = new connectWindow();
    waitScreen = new waitWindow();
    targetScreen = new targetWindow();
    actionScreen = new actionWindow();

    stack = new QStackedWidget(this);
    stack -> setFixedSize(screenW, screenH);
    stack -> addWidget(connectScreen);
    stack -> addWidget(waitScreen);
    stack-> addWidget(targetScreen);
    stack -> addWidget(actionScreen);

    connect(connectScreen->connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(connectScreen->disconnectButton, SIGNAL(clicked()), this, SLOT(disconnectFromServer()));
    connect(waitScreen->cancel, SIGNAL(clicked()), this, SLOT(waitCancelled()));
    connect(targetScreen->back, SIGNAL (clicked()), this, SLOT (targetScreenCancelled()));
    connect(targetScreen, SIGNAL(sendTarget(int)), this, SLOT(slotSendTarget(int)));
    connect(actionScreen->move, SIGNAL(clicked()), this, SLOT(slotSendMove()));
    connect(actionScreen->cancel, SIGNAL(clicked()), this, SLOT(slotSendCancel()));
    connect(actionScreen->back, SIGNAL(clicked()), this, SLOT(actionScreenCancelled()));

}

void mainwindow::connectToServer()
{
    //Establish Connection
    char* hostname = "localhost" ;
    int portNum = 18944;
    socket = igtl::ClientSocket::New();
    int r = socket->ConnectToServer(hostname, portNum);

    if (r != 0)
    {
        connectScreen->connectButton -> setText("No connection - Try Again");
    }

    else
    {
        socket -> SetReceiveTimeout(250);
        statMsg = igtl::StatusMessage::New();

        //do connection handshake
        sendMessage("TouchscreenHandshake");

        if(strcmp(receiveMessage(), "SlicerHandshake") == 0)
        {
            //move to wait window
            stack -> setCurrentWidget(waitScreen);
            sendMessage("NumberOfTargets");
            receiveNumberOfTargets();

            connectScreen->connectButton -> setText("Connected");
            connectScreen->connectButton -> setEnabled(false);
            connectScreen->disconnectButton -> setEnabled(true);
            connectScreen->disconnectButton -> setText("Disconnect");
        }

        else
        {
            connectScreen->connectButton -> setText("No connection - Try Again");
        }
    }
}

void mainwindow::disconnectFromServer()
{
    socket->CloseSocket();

    connectScreen ->disconnectButton -> setText("Disconnected");
    connectScreen ->disconnectButton -> setEnabled(false);

    connectScreen ->connectButton -> setEnabled(true);
    connectScreen ->connectButton -> setText("Connect");
}

void mainwindow::sendMessage(const char* msg)
{
    statMsg -> SetCode(1);
    statMsg -> SetStatusString(msg);
    statMsg->Pack();
    socket->Send(statMsg->GetPackPointer(), statMsg->GetPackSize());
    qDebug() << "Sent: " << statMsg -> GetStatusString();
}

const char* mainwindow::receiveMessage()
{
    igtl::MessageHeader::Pointer headerMsg;
    headerMsg = igtl::MessageHeader::New();
    const char* message = "";

    headerMsg->InitPack();
    int r = socket->Receive(headerMsg -> GetPackPointer(), headerMsg->GetPackSize());
    if (r == 0)
    {
        message = "error";
    }

    if (r != headerMsg->GetPackSize())
    {
        message = "noMessage";
    }

    headerMsg->Unpack();

    recMsg = igtl::StatusMessage::New();

    recMsg->SetMessageHeader(headerMsg);
    recMsg->AllocatePack();

    // Receive data from the socket
    socket->Receive(recMsg->GetPackBodyPointer(), recMsg->GetPackBodySize());

    recMsg->Unpack();

    if (recMsg->GetCode() == 2) // correct code from slicer
         {
              message = recMsg -> GetStatusString();
          }
    qDebug() <<"Received: " << message;
    return message;

}

void mainwindow::waitCancelled()
{
    stack->setCurrentWidget(connectScreen);
}

void mainwindow::receiveNumberOfTargets()
{
    bool noTargets = true;
    const char* received;
    int numTar = 0;

    while (noTargets)
    {
        received = receiveMessage();

        if (strcmp(received, "noMessage") == 0) //slicer didn't send anything
        {
            //process events
            QEventLoop eventloop(this);
            eventloop.processEvents();
            eventloop.exit();
            continue;
        }

        else if (strcmp(received, "error") == 0)
        {
            break;
        }

        else if(strcmp(received, "") != 0) //message was received
        {
            if (strlen(received) > 1)
            {
                std::string sReceived = received;
                int loc = sReceived.find(",");
                char num = sReceived[loc +1];
                numTar = num - '0';
            }

            else
            {
                numTar = atoi(received);
            }
        }

        if (numTar != 0) //have targets
        {
            noTargets = false;
            break;
        }

      } //end loop

    targetScreen -> buildTargets(numTar);
    stack -> setCurrentWidget(targetScreen);


} //end function

void mainwindow::targetScreenCancelled()
{
    stack -> setCurrentWidget(connectScreen);
}

void mainwindow::slotSendTarget(int num)
{
    const char* msg = "SendTarget";
    std::stringstream fullMsg;
    fullMsg << msg << num;
    const char* targetMsg = fullMsg.str().c_str();

    sendMessage(targetMsg);

    //receive depth
    std::string depth = receiveMessage();

    actionScreen -> displayDepth(depth);
    actionScreen -> displayTarget(num);
    stack -> setCurrentWidget(actionScreen);

}

void mainwindow::slotSendMove()
{
    sendMessage("MoveRobot");
    if (strcmp(receiveMessage(), "Moving") == 0)
    {
        actionScreen -> move -> setText("Moving...");
        actionScreen->move->setEnabled(false);
    }
    else
    {
        actionScreen ->move->setText("Error-Try again");
    }
}

void mainwindow::slotSendCancel()
{
    actionScreen-> tarCancel -> setVisible(true);
    actionScreen -> move -> setEnabled(false);
    actionScreen -> cancel -> setEnabled(false);
    sendMessage("CancelTarget");
    receiveMessage();
}

void mainwindow::actionScreenCancelled()
{
    sendMessage("CancelTarget");
    receiveMessage();

    //reset screen
    actionScreen->move -> setEnabled(true);
    actionScreen->move->setText("Move robot");
    actionScreen->tarCancel -> setVisible(false);
    actionScreen->cancel -> setEnabled(true);

    //go back to target selection
    stack -> setCurrentWidget(targetScreen);
}
