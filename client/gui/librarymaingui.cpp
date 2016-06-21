#include "librarymaingui.h"
#include "add+editbook.h"

#include <iostream>

namespace library{

MainGUI::MainGUI( QWidget *vParent ) : QMainWindow(vParent),
									   mClient(nullptr),
									   io_service(),
									   resolver(io_service),
									   s(io_service) {
    setupUi(this);
    pTERecive->setReadOnly(true);

    connect(bConnect, SIGNAL(clicked(bool)), this, SLOT(connectToServer(bool)));
    connect(bSend, SIGNAL(clicked(bool)), this, SLOT(sendData(bool)));
    connect(lESend, SIGNAL(returnPressed()), this, SLOT(sendData()));
	connect(bAddBook, SIGNAL(clicked(bool)), this, SLOT(addBook(bool)));

	connect(this, SIGNAL(sendMessage(QString)), this, SLOT(messageNetwork(QString)));



    
};


void MainGUI::addBook( bool vChecked ) {
		AddEditBook vAddEditBookDialog;
		vAddEditBookDialog.setWindowTitle("Add Book");
		vAddEditBookDialog.exec();
		if( vAddEditBookDialog.result() == QDialog::Accepted ){
			if(mClient != nullptr){
				std::string data = "";

				data = vAddEditBookDialog.lETitle->text().toStdString() + ";";
				data +=vAddEditBookDialog.lEAuthor->text().toStdString() + ";";
				data +=vAddEditBookDialog.lEPublisher->text().toStdString() + ";";
				data +=vAddEditBookDialog.lEISBN->text().toStdString() + ";";
				data +=vAddEditBookDialog.lEDate->text().toStdString();

				mClient->write("User1","add#book", data);
			}
		}
	};




	void MainGUI::connectToServer(bool){

    if(mClient == nullptr) {

		try{
			endpoint_iterator = resolver.resolve({lEIP->text().toStdString(), lEPort->text().toStdString()});
			mClient = new Client(io_service, endpoint_iterator, s);
			connect(mClient, SIGNAL(networkActivity(QString)), this, SLOT(getData(QString)));
			bConnect->disconnect();
			connect(bConnect, SIGNAL(clicked(bool)), this, SLOT(disconnectFromServer(bool)));
			bConnect->setText("Disconnect");
			pTERecive->appendPlainText( "Connect to server: " + lEIP->text() + ":" + lEPort->text());
			lEIP->setReadOnly(true);
			lEPort->setReadOnly(true);

		} catch (std::exception& e){
			emit sendMessage( QString(e.what()) );
		}
	}

};



void MainGUI::disconnectFromServer(bool){

		if(mClient != nullptr){
			delete mClient;
			mClient = nullptr;

			bConnect->disconnect();
			connect(bConnect, SIGNAL(clicked(bool)), this, SLOT(connectToServer(bool)));
			bConnect->setText("Connect");
			pTERecive->appendPlainText( "Disconnect from server");
			lEIP->setReadOnly(false);
			lEPort->setReadOnly(false);
		}
};




void MainGUI::sendData(bool){
    if(mClient != nullptr){
        mClient->write(lESend->text().toStdString(),"","");
    }
};

void MainGUI::getData(QString aData){
    pTERecive->appendPlainText( aData );
};

void MainGUI::messageNetwork(QString aMessage ){
	pTERecive->appendPlainText(aMessage);

};

}

