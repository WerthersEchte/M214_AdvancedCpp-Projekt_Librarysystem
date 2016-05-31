#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include "./networkconnection.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <thread>
#include <vector>
#include <string>

#include "core/library.h"

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) :
        socket_(boost::move(socket))
    { }

    void NetworkConnection::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred) { }

    void NetworkConnection::receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {
        std::cout << "Receive message" << std::endl;
        std::cout.write(buffer, bytes_transferred);
        std::cout << std::endl;

        std::string vMessage(buffer, bytes_transferred);
        std::vector< std::string > vMessageParts;

        boost::split( vMessageParts,
                      vMessage,
                      [](char aCharacter) { return aCharacter == 7; } );

        for(std::string vPart : vMessageParts ){
            std::cout << vPart << std::endl;
        }

        if(!vMessageParts[0].compare("book")){
            Library::getLibrary()->parseCommand( vMessageParts[1] );
        }

        boost::asio::async_write(socket_, boost::asio::buffer(buffer, bytes_transferred), std::bind(&NetworkConnection::writeHandler, this, std::placeholders::_1, std::placeholders::_2));
    }

    void NetworkConnection::start() {

        try {

            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, this, std::placeholders::_1, std::placeholders::_2));
            std::cout << "New client connected on " << socket_.remote_endpoint().address().to_string() << ":" << socket_.remote_endpoint().port() << std::endl;

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
            socket_.close();
        }

    }
}
