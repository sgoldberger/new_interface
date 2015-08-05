#include "waitwindow.h"
#include <QDebug>

waitWindow::waitWindow(QWidget* parent):
    QWidget(parent)
{
    //set window
    //const QRect screenSize = desktop->screenGeometry();
    int screenW = 800;
    int screenH = 600;
    //setGeometry(0,0,800,600);
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

   bool noTargets = true;
   int numTar = 0;

   igtl::MessageHeader::Pointer headerMsg;
   headerMsg = igtl::MessageHeader::New();

   //loop trying to receive
   /*
   while(noTargets && this->isVisible())
   {
       headerMsg->InitPack();
       int r = socket->Receive(headerMsg -> GetPackPointer(), headerMsg->GetPackSize());
       if (r == 0)
         {
              socket->CloseSocket();
              //exit(0);
         }
        if (r != headerMsg->GetPackSize())
         {

            QEventLoop eventloop(this);
            eventloop.processEvents();
            eventloop.exit();
            continue;
         }

      // Deserialize the header
      headerMsg->Unpack();
      if (strcmp(headerMsg->GetDeviceType(), "STATUS") == 0)
      {
         statMsg->SetMessageHeader(headerMsg);
         statMsg->AllocatePack();

         // Receive transform data from the socket
         socket->Receive(statMsg->GetPackBodyPointer(), statMsg->GetPackBodySize());

         // Deserialize the transform data
         statMsg->Unpack();
           qDebug() << "Received: " << statMsg-> GetStatusString();

        // Retrive the status data
        if (statMsg->GetCode() == 2) //from slicer
        {
           //get number of targets
           std::string strMsg = statMsg ->GetStatusString();

           if (strMsg.length() > 1) //"NewNumberTargets"
           {
               int loc = strMsg.find(",");
               char num = strMsg[loc +1];
               numTar = num - '0';

           }
           else
           {
               numTar = atoi(strMsg.c_str());
           }

           if (numTar != 0)
           {
              noTargets = false; //received number of targets
              emit sendNumTar(socket, statMsg, numTar);//moveto window 2
              this -> hide();
              break;
           }
         }
        else //error - wrong code sent
        {
            continue;
        }

     }

} //end of loop*/

} //end of function

