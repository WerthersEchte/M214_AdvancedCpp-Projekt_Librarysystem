#include "librarymaingui.h"

#include <iostream>

namespace library{

MainGUI::MainGUI( QWidget *vParent )
    : QMainWindow(vParent),
    mClient(nullptr),
    io_service(),
    resolver(io_service),
    s(io_service)
{
    setupUi(this);

    pTERecive->setReadOnly(true);

    connect(bConnect, SIGNAL(clicked(bool)), this, SLOT(connectToServer(bool)));
    connect(bSend, SIGNAL(clicked(bool)), this, SLOT(sendData(bool)));
};

void MainGUI::connectToServer(bool){

    endpoint_iterator = resolver.resolve({lEIP->text().toStdString(), lEPort->text().toStdString()});

    mClient = new Client(io_service, endpoint_iterator, s);
};
void MainGUI::sendData(bool){
    if(mClient != nullptr){
        mClient->write(lESend->text().toStdString(),"","");
    }
};
void MainGUI::getData(QString aData){
};

}

