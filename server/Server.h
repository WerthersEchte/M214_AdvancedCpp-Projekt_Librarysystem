/*
 * Server.h
 *
 *  Created on: 19 Apr 2016
 *      Author: orobsonpires
 */

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace library {

class Server {
public:
	Server(boost::asio::io_service& io_service, short port);
	virtual ~Server();

private:
  void do_accept();
  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

}
