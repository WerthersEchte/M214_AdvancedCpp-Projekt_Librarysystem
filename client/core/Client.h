#pragma once

/*
 * Client.h
 *
 *  Created on: 24 Apr 2016
 *      Author: orobsonpires
 */

#include <boost/asio.hpp>
#include <QObject>
#include <QString>

namespace library {
using boost::asio::ip::tcp;

enum { max_length = 1024 };

class Client: public QObject{

    Q_OBJECT

public:
	Client(boost::asio::io_service& io_service,
	      tcp::resolver::iterator& endpoint_iterator,  tcp::socket& socket);
	~Client();

	void write(std::string data);
signals:
    void networkActivity( QString aActivity );
	//void changeLoginButton(bool state);
	void closeServerConnection(bool state);

private:
	void do_connect(tcp::resolver::iterator endpoint_iterator);
	boost::asio::io_service& io_service_;
	tcp::socket& socket_;
};

}
