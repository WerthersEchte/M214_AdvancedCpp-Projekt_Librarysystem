#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include "core/networkconnection.h"
#include <memory>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)), timer_(socket_.get_io_service()), strand_(socket_.get_io_service()) { }


    void NetworkConnection::start() {
        auto self(shared_from_this());
        boost::asio::spawn(strand_,
                           [this, self](boost::asio::yield_context yield) {
                               try {
                                   char data[READ_DATA_BUFFER_LENGTH];

                                   for (;;) {
                                      // timer_.expires_from_now(std::chrono::seconds(10));
                                       boost::system::error_code error;

                                       size_t len = socket_.read_some(boost::asio::buffer(data, READ_DATA_BUFFER_LENGTH), error);
                                       //size_t len = socket_.async_read_some(boost::asio::buffer(data), error);

                                       //std::cout.write(data, READ_DATA_BUFFER_LENGTH);
                                       boost::asio::async_write(socket_, boost::asio::buffer(data, len), yield);
                                   }
                               }
                               catch (std::exception& e)
                               {
                                   socket_.close();
                                   timer_.cancel();
                               }
                           });

        boost::asio::spawn(strand_,
                           [this, self](boost::asio::yield_context yield) {
                               while (socket_.is_open()) {
                                   boost::system::error_code ignored_ec;
                                   timer_.async_wait(yield[ignored_ec]);
                                   if (timer_.expires_from_now() <= std::chrono::seconds(0))
                                       socket_.close();
                               }
                           });
    }
}