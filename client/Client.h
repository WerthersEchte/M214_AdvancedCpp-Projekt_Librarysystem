/*
 * Client.h
 *
 *  Created on: 24 Apr 2016
 *      Author: orobsonpires
 */

#include <boost/asio.hpp>

namespace library {
using boost::asio::ip::tcp;

enum { max_length = 1024 };

class Client {
public:
	Client(boost::asio::io_service& io_service,
	      tcp::resolver::iterator& endpoint_iterator,  tcp::socket& socket);
	~Client();

	void write(std::string user, std::string action, std::string data );
private:
	void do_connect(tcp::resolver::iterator endpoint_iterator);
	boost::asio::io_service& io_service_;
	tcp::socket& socket_;
};

}
