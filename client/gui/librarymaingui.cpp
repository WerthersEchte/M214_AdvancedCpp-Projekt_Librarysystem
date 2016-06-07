#include "librarymaingui.h"

namespace library{

MainGUI::MainGUI( QWidget *vParent )
    : QMainWindow(vParent),
    mClient(nullptr)
{
    setupUi(this);

    pTERecive->setReadOnly(true);

    connect(bConnect, SIGNAL(clicked(bool)), this, SLOT(connectToServer(bool)));
    connect(bSend, SIGNAL(clicked(bool)), this, SLOT(sendData(bool)));
};
    
void MainGUI::connectToServer(bool){

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    auto endpoint_iterator = resolver.resolve({lEIP->text().toStdString(), lEPort->text().toStdString()});
    boost::asio::ip::tcp::socket s(io_service);
    
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

