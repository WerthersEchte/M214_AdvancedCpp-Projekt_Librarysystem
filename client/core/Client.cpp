/*
 * Client.cpp
 *
 *  Created on: 24 Apr 2016
 *      Author: orobsonpires
 */

#include "Client.h"
#include <iostream>
#include "core/definitions.h"
namespace library {

	Client::Client(boost::asio::io_service& io_service,
				   tcp::resolver::iterator& endpoint_iterator,
				   tcp::socket& socket) : io_service_(io_service), socket_(socket) {
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

		//Wait and receive the response
		char reply[max_length];
		size_t reply_length;
		QString receiveData = "";
		do {
			reply_length = socket_.receive(boost::asio::buffer(reply, max_length));
			receiveData.append(QByteArray(reply, reply_length ) );
		} while (receiveData[receiveData.length()-1] != 7);
		receiveData.chop(1);  //Remove the EOT char

		emit networkActivity(receiveData);
		//Get the command from the response. The cmd max length is 10
		std::string cmd = "";
		for (int i=0; i<receiveData.length() || i>10; i++){
			if(receiveData.at(i).toLatin1() == static_cast<char>(Splitter::TYPE)){
				receiveData.remove(0, i+1);
				break;
			}
			else cmd += receiveData.at(i).toLatin1();
		}


		//Process cmd
		if(cmd == library::command::LOGIN && receiveData == "false") emit closeServerConnection(true);
		else if(cmd == library::command::LOGOUT) emit closeServerConnection(true);

	}

	void Client::do_connect(tcp::resolver::iterator endpoint_iterator) {
			boost::asio::connect(socket_, endpoint_iterator);
	}

}
