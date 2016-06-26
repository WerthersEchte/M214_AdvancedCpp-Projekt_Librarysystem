#ifndef _LibraryMainGUI_
#define _LibraryMainGUI_

#include "ui_mainwindow.h"
#include "core/Client.h"

#include <QWidget>
#include <QMainWindow>
#include <QString>

namespace library{

class MainGUI: public QMainWindow, private Ui::ClientMainGUI {
    Q_OBJECT

    boost::asio::ip::tcp::resolver::iterator endpoint_iterator;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket s;
    Client* mClient;
	std::string pendingUser;

	void userLogin();
	void userLogout();

public:
    MainGUI( QWidget *vParent = 0 );

signals:
	void sendMessage( QString msg );
	//void changeLoginButton(bool state);


private slots:
    void connectToServer(bool);
	void disconnectFromServer(bool);
	void messageNetwork(QString aMessage );
    void sendData(bool=true);
	void addBook(bool vChecked);
	void searchBook(bool vChecked);
	//;
	void getBook(bool vChecked);
	void editBook(bool vChecked);
	//
	//void changeLoginButton(bool state);

public slots:
    void getData(QString aData);

};

}

#endif // _LibraryMainGUI_
