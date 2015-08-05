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
    connect(actionScreen->cancel, SIGNAL(clicked()), this, SLOT(actionScreenCancelled()));
    //connect(actionScreen->back, SIGNAL(clicked()), this, SLOT(actionScreenCancelled()));
    connect(this, SIGNAL(targetChange(int)), this, SLOT(slotTargetChange(int)));
    connect(connectScreen->viewTargetsButton, SIGNAL(clicked()), this, SLOT(slotViewTargetScreen()));

}
/*
 * establish connection through openIGTlink to slicer server
*/
void mainwindow::connectToServer()
{
    //Establish Connection
    char* hostname = connectScreen->getIp();
    int portNum = connectScreen ->getPort();
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
            connectScreen->connectButton -> setText("Connected");
            connectScreen->connectButton -> setEnabled(false);
            connectScreen->disconnectButton -> setEnabled(true);
            connectScreen->disconnectButton -> setText("Disconnect");

            stack -> setCurrentWidget(waitScreen);
            sendMessage("NumberOfTargets");
            receiveNumberOfTargets();
        }

        else
        {
            connectScreen->connectButton -> setText("No connection - Try Again");
        }
    }
}

/*
 * end connection through openIGTlink to slicer server
*/
void mainwindow::disconnectFromServer()
{
    socket->CloseSocket();

    connectScreen ->disconnectButton -> setText("Disconnected");
    connectScreen ->disconnectButton -> setEnabled(false);

    connectScreen ->connectButton -> setEnabled(true);
    connectScreen ->connectButton -> setText("Connect");
}


/*
 * send string message through openIGTlink to slicer server
*/
void mainwindow::sendMessage(const char* msg)
{
    statMsg -> SetCode(1);
    statMsg -> SetStatusString(msg);
    statMsg->Pack();
    socket->Send(statMsg->GetPackPointer(), statMsg->GetPackSize());
    qDebug() << "Sent: " << statMsg -> GetStatusString();
}


/*
 * receive string message through openIGTlink to slicer server
*/
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

    else if (r != headerMsg->GetPackSize())
    {
        message = "noMessage";
    }

    else
    {
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
    }

    qDebug() <<"Received: " << message;
    return message;

}

/*
 * go back button clicked in wait screen, return to connection screen
*/
void mainwindow::waitCancelled()
{
    stack->setCurrentWidget(connectScreen);
}

/*
 * initial loop to receive number of targets from slicer
*/
void mainwindow::receiveNumberOfTargets()
{
    bool noTargets = true;
    const char* received;

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
            if (strncmp(received, "NewNumberOfTargets",18) == 0)
            {
                std::string sReceived = received;
                int loc = sReceived.find(",");
                char num = sReceived[loc +1];
                numTar = num - '0';
            }

            else if (strlen(received)==1)
            {
                numTar = atoi(received);
            }

            //check other cases (cancelled, moving, done moving)
        }

        if (numTar != 0) //have targets
        {
            noTargets = false;
            break;
        }

      } //end loop

    targetScreen -> buildTargets(numTar);
    stack -> setCurrentWidget(targetScreen);
    listen(numTar);


} //end function

/*
 * loop to check if number of targets in slicer has changed and rebuild target screen accordingly
*/
void mainwindow::listen(int num)
{
    int currentNumTar = num;
    bool noChange = true;
    const char* received;

    while (noChange)
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
            if (strncmp(received, "NewNumberOfTargets",18) == 0)
            {
                std::string sReceived = received;
                int loc = sReceived.find(",");
                char num = sReceived[loc +1];
                numTar = num - '0';
            }

            else if (strlen(received)==1)
            {
                numTar = atoi(received);
            }

            //check other cases (cancelled, moving, done moving)
        }

        if (numTar != 0) //have targets
        {
            currentNumTar = numTar;
            noChange = false;
            emit targetChange(currentNumTar);
        }

        else //deleted all targets
        {
            noChange = false;
            stack -> setCurrentWidget(waitScreen);
            receiveNumberOfTargets();
        }

      } //end loop
}

/*
 * rebuild target screen with new number of targets
*/
void mainwindow::slotTargetChange(int num)
{
   if (stack-> currentWidget() == actionScreen)
    {
        stack->setCurrentWidget(targetScreen);
        actionScreen -> reset();
    }

   targetScreen -> refresh();
   targetScreen -> buildTargets(num);
   listen(num);
}

/*
 * back button clicked in target screen, return to connection screen
*/
void mainwindow::targetScreenCancelled()
{
    stack -> setCurrentWidget(connectScreen);
    connectScreen->viewTargetsButton->setVisible(true);
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

/*
 * move button clicked in action screen, send move command to slicer
*/
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

/*
void mainwindow::slotSendCancel()
{
    actionScreen-> tarCancel -> setVisible(true);
    actionScreen -> move -> setEnabled(false);
    actionScreen -> cancel -> setEnabled(false);
    sendMessage("CancelTarget");
    receiveMessage();
}
*/

/*
 * cancel button clicked in action screen, send cancel command to slicer and return to target screen
*/
void mainwindow::actionScreenCancelled()
{
    sendMessage("CancelTarget");
    receiveMessage();

    //reset screen
    actionScreen->move -> setEnabled(true);
    actionScreen->move->setText("Move robot");
    //actionScreen->tarCancel -> setVisible(false);
    actionScreen->cancel -> setEnabled(true);

    //go back to target selection
    stack -> setCurrentWidget(targetScreen);
}

/*
 * return to target screen from connect screen
*/
void mainwindow::slotViewTargetScreen()
{
   stack -> setCurrentWidget(targetScreen);
}
