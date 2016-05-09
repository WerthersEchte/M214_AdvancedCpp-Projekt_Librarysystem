/*
 * session.h
 *
 *  Created on: 19 Apr 2016
 *      Author: orobsonpires
 */

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace library {

class Session : public std::enable_shared_from_this<Session>{

public:
	Session(tcp::socket socket);
	void start();
	virtual ~Session();
private:
	void do_read();
	void do_write(std::size_t length);

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};

}
