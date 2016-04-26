/*
 * Server.cpp
 *
 *  Created on: 19 Apr 2016
 *      Author: orobsonpires
 */

#include "Server.h"
#include "Session.cpp"

namespace library {

Server::~Server() {
};

Server::Server(boost::asio::io_service& io_service, short port) :
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), socket_(
				io_service) {
	do_accept();
};

void Server::do_accept() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
	{
		if (!ec)
		{
			std::make_shared<Session>(std::move(socket_))->start();
		}

		do_accept();
	});
};

}
