/*
 * Client.cpp
 *
 *  Created on: 24 Apr 2016
 *      Author: orobsonpires
 */

#include "Client.h"

namespace library {

Client::Client(boost::asio::io_service& io_service,
		tcp::resolver::iterator& endpoint_iterator, tcp::socket& socket) :
		io_service_(io_service), socket_(socket) {
	do_connect(endpoint_iterator);
	emit networkActivity( QString("Connected") );
}
;

Client::~Client() {
}
;

void Client::write(std::string user, std::string action, std::string data) {

	char request[max_length];

	std::string fullData = "";

	fullData.append(user).append(action).append(data);

	strncpy(request, fullData.c_str(), sizeof(request));

	size_t request_length = std::strlen(request);

	boost::asio::write(socket_, boost::asio::buffer(request, request_length));

	char reply[max_length];

	size_t reply_length = socket_.receive( boost::asio::buffer(reply, max_length) );

	emit networkActivity( QString( QByteArray(reply, reply_length ) ) );

}

void Client::do_connect(tcp::resolver::iterator endpoint_iterator) {
	boost::asio::connect(socket_, endpoint_iterator);
}

}
