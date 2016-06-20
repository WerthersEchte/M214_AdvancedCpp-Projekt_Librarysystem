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

public:
    MainGUI( QWidget *vParent = 0 );

signals:
	void sendMessage( QString msg );

private slots:
    void connectToServer(bool);
	void disconnectFromServer(bool);
	void messageNetwork(QString aMessage );
    void sendData(bool);

public slots:
    void getData(QString aData);

};

}

#endif // _LibraryMainGUI_
