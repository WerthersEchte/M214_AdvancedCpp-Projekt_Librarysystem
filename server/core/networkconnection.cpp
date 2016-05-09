#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include "./networkconnection.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <thread>

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) : socket_(boost::move(socket)) { }

    void NetworkConnection::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred) { }

    void NetworkConnection::receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {
        std::cout << "Receive message" << std::endl;
        std::cout.write(buffer, bytes_transferred);
        std::cout << std::endl;
        boost::asio::async_write(socket_, boost::asio::buffer(buffer, bytes_transferred), std::bind(&NetworkConnection::writeHandler, this, std::placeholders::_1, std::placeholders::_2));
    }

    void NetworkConnection::start() {

        try {

            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, this, std::placeholders::_1, std::placeholders::_2));

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
            socket_.close();
        }

    }
}