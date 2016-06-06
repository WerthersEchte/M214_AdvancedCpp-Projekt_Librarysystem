#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include "./networkconnection.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "./library.h"
#include <string>
#include <boost/algorithm/string.hpp>

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) : socket_(boost::move(socket)) { }

    void NetworkConnection::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred) { }

    void NetworkConnection::receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {


        std::cout << error.value() << " - " << (int)boost::asio::error::connection_reset << std::endl;

        if ((error.value() == boost::asio::error::connection_reset) || (error.value() == boost::asio::error::eof)){
            std::cout << "Client disconnect!" << std::endl;
            socket_.close();

        } else {

            std::vector<string> strs;
            boost::split(strs, buffer, boost::is_any_of(";"));

            string responseType = strs.at(0);

            if (responseType == "book" && strs.size() >= 2) {
                string responseSubType = strs.at(1);

                if (responseSubType == "add" && strs.size() >= 3) {
                    string responseData = strs.at(2);
                    std::cout << "Add book" << std::endl;
                }

            } else {
                std::cout << "Receive message: ";
                std::cout.write(buffer, bytes_transferred) << std::endl;
            }

            boost::asio::async_write(socket_, boost::asio::buffer(buffer, bytes_transferred), std::bind(&NetworkConnection::writeHandler, this, std::placeholders::_1, std::placeholders::_2));

            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, this, std::placeholders::_1, std::placeholders::_2));
        }
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