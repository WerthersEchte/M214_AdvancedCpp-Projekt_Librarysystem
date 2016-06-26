/*
 * Client.cpp
 *
 *  Created on: 24 Apr 2016
 *      Author: orobsonpires
 */

#include "Client.h"
#include <iostream>
namespace library {

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator& endpoint_iterator, tcp::socket& socket) : io_service_(io_service), socket_(socket) {
	do_connect(endpoint_iterator);
};

Client::~Client() {
	socket_.close();
};

void Client::write(std::string data) {
	char request[max_length];
	std::string fullData = "";
	fullData.append(data);
    if(fullData.empty()){
        return;
    }
	strncpy(request, fullData.c_str(), sizeof(request));
	size_t request_length = std::strlen(request);

	boost::asio::write(socket_, boost::asio::buffer(request, request_length));
	char reply[max_length];
	size_t reply_length;
	QString receiveData = "";

	do {
		reply_length = socket_.receive(boost::asio::buffer(reply, max_length));
		receiveData.append(QByteArray(reply, reply_length ) );
	} while (receiveData[receiveData.length()-1] != 7);
    std::cout << std::endl;

    //emit networkActivity( QString( QByteArray(reply, reply_length ) ) );
    emit networkActivity(receiveData);
}

void Client::do_connect(tcp::resolver::iterator endpoint_iterator) {
		boost::asio::connect(socket_, endpoint_iterator);
}

}
