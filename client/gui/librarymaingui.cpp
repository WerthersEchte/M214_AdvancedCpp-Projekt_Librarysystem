#include "librarymaingui.h"
#include "add+editbook.h"
#include "definitions.h"
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
	connect(bEditBook, SIGNAL(clicked(bool)), this, SLOT(editBook(bool)));
	connect(bSearchBook, SIGNAL(clicked(bool)), this, SLOT(searchBook(bool)));
	connect(bBorrowBook, SIGNAL(clicked(bool)), this, SLOT(borrowBook(bool)));
	connect(bReturnBook, SIGNAL(clicked(bool)), this, SLOT(returnBook(bool)));
	connect(bGetBook, SIGNAL(clicked(bool)), this, SLOT(getBook(bool)));
	connect(bGetUser, SIGNAL(clicked(bool)), this, SLOT(getUser(bool)));
	connect(bGetBorrowed, SIGNAL(clicked(bool)), this, SLOT(getBorrowedBooks(bool)));
	connect(bChangePassword, SIGNAL(clicked(bool)), this, SLOT(changeUserPassword(bool)));
	connect(bChangePassword, SIGNAL(clicked(bool)), this, SLOT(changeUserPassword(bool)));
	connect(bAddUser, SIGNAL(clicked(bool)), this, SLOT(addUser(bool)));

	connect(this, SIGNAL(sendMessage(QString)), this, SLOT(messageNetwork(QString)));
};

	/****************************************
	 * Book implementation
	 ****************************************/

	void MainGUI::getBook( bool vChecked ) {
		if(mClient != nullptr){
			std::string data = library::command::BOOK + static_cast<char>(library::Splitter::TYPE) + library::command::book::GET + static_cast<char>(library::Splitter::COMMAND);
			data += lEBook->text().toStdString();
			mClient->write(data);
		}
	};



	void MainGUI::editBook( bool vChecked ) {
		if(mClient != nullptr){
			std::string data = library::command::BOOK + static_cast<char>(library::Splitter::TYPE) + library::command::book::EDIT + static_cast<char>(library::Splitter::COMMAND);
			data += lEBook->text().toStdString();
			mClient->write(data);
		}
	};



	void MainGUI::borrowBook( bool vChecked ) {
		if(mClient != nullptr){
			std::string data = library::command::BOOK + static_cast<char>(library::Splitter::TYPE) + library::command::book::BURROW + static_cast<char>(library::Splitter::COMMAND);
			data += lEBook->text().toStdString();
			mClient->write(data);
		}
	};



	void MainGUI::returnBook( bool vChecked ) {
		if(mClient != nullptr){
			std::string data = library::command::BOOK + static_cast<char>(library::Splitter::TYPE) + library::command::book::RETURN + static_cast<char>(library::Splitter::COMMAND);
			data += lEBook->text().toStdString();
			mClient->write(data);
		}
	};



	void MainGUI::addBook( bool vChecked ) {
		AddEditBook vAddEditBookDialog;
		vAddEditBookDialog.setWindowTitle("Add Book");
		vAddEditBookDialog.exec();
		if( vAddEditBookDialog.result() == QDialog::Accepted ){
			if(mClient != nullptr){
				std::string data = library::command::BOOK + static_cast<char>(library::Splitter::TYPE) + library::command::book::ADD + static_cast<char>(library::Splitter::COMMAND);
				data += vAddEditBookDialog.lETitle->text().toStdString() + static_cast<char>(library::Splitter::COMMAND);
				data +=vAddEditBookDialog.lEAuthor->text().toStdString() + static_cast<char>(library::Splitter::COMMAND);
				data +=vAddEditBookDialog.lEPublisher->text().toStdString() + static_cast<char>(library::Splitter::COMMAND);
				data +=vAddEditBookDialog.lEISBN->text().toStdString() + static_cast<char>(library::Splitter::COMMAND);
				data +=vAddEditBookDialog.lEDate->text().toStdString();
				mClient->write(data);
			}
		}
	};



	void MainGUI::searchBook(bool vChecked){
		if(mClient != nullptr){
			std::string data = library::command::BOOK + static_cast<char>(library::Splitter::TYPE) + library::command::book::SEARCH + static_cast<char>(library::Splitter::COMMAND);
			data += lEBook->text().toStdString();
			mClient->write(data);
		}
	};



	/****************************************
	 * User implementation
	 ****************************************/
	void MainGUI::addUser(bool vChecked){
		if(mClient != nullptr){
			std::string data = library::command::USER + static_cast<char>(library::Splitter::TYPE) + library::command::user::ADD + static_cast<char>(library::Splitter::COMMAND);
			data += lEUser->text().toStdString();
			mClient->write(data);
		}
	};

	void MainGUI::changeUserPassword(bool vChecked){
		if(mClient != nullptr){
			std::string data = library::command::USER + static_cast<char>(library::Splitter::TYPE) + library::command::user::CHANGEPASSWORD + static_cast<char>(library::Splitter::COMMAND);
			data += lEUser->text().toStdString();
			mClient->write(data);
		}
	};

	void MainGUI::getUser(bool vChecked){
		if(mClient != nullptr){
			std::string data = library::command::USER + static_cast<char>(library::Splitter::TYPE) + library::command::user::GET + static_cast<char>(library::Splitter::COMMAND);
			data += lEUser->text().toStdString();
			mClient->write(data);
		}
	};

	void MainGUI::getBorrowedBooks(bool vChecked){
		if(mClient != nullptr){
			std::string data = library::command::USER + static_cast<char>(library::Splitter::TYPE) + library::command::user::BORROWEDBOOKS;
			data += lEUser->text().toStdString();
			mClient->write(data);
		}
	};



	/*******************************************
	 * Network implenetation
	 *******************************************/

	void MainGUI::userLogin(){
		if(mClient != nullptr){
			std::string data = library::command::LOGIN + static_cast<char>(library::Splitter::TYPE);
			data += lEUserLogin->text().toStdString();
			mClient->write(data);
			//lEUserLogin->setReadOnly(true);
		}
	};



	void MainGUI::userLogout(){
		if(mClient != nullptr){
			std::string data = library::command::LOGOUT;
			mClient->write(data);
		}
		//lEUserLogin->setReadOnly(false);;
	};



	void MainGUI::connectToServer(bool){
		if(mClient == nullptr) {
			try{
				endpoint_iterator = resolver.resolve({lEIP->text().toStdString(), lEPort->text().toStdString()});
				mClient = new Client(io_service, endpoint_iterator, s);

				connect(mClient, SIGNAL(networkActivity(QString)), this, SLOT(messageNetwork(QString)));
				connect(mClient, SIGNAL(bookActivity(QString)), this, SLOT(messageBook(QString)));
				connect(mClient, SIGNAL(userActivity(QString)), this, SLOT(messageUser(QString)));
				connect(mClient, SIGNAL(closeServerConnection(bool)), this, SLOT(disconnectFromServer(bool)));

				bConnect->disconnect();
				connect(bConnect, SIGNAL(clicked(bool)), this, SLOT(disconnectFromServer(bool)));

				bConnect->setText("Disconnect");
				pTERecive->appendPlainText( "Connect to server: " + lEIP->text() + ":" + lEPort->text());
				lEIP->setReadOnly(true);
				lEPort->setReadOnly(true);
				userLogin();
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
			pTERecive->appendPlainText("Disconnect from server");
			lEIP->setReadOnly(false);
			lEPort->setReadOnly(false);
			//userLogout();
			//lEUserLogin->setReadOnly(false);
		}
	};



	void MainGUI::sendData(bool){
		if(mClient != nullptr){
			mClient->write(lESend->text().toStdString());
		}
	};



	void MainGUI::messageNetwork(QString aMessage ){
		pTERecive->appendPlainText(aMessage);
	};



	void MainGUI::messageBook(QString aMessage ){
		pTEBookReceive->appendPlainText(aMessage);
	};



	void MainGUI::messageUser(QString aMessage ){
		pTEUser->appendPlainText(aMessage);
	};
}

