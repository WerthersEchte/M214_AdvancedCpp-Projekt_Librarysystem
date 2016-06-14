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
#include <iostream>

#include <QString>

#include "core/library.h"

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) :
        socket_(boost::move(socket)),
        mId(QString("Client(").append( QString::fromUtf8(socket.remote_endpoint().address().to_string().c_str() ) ).append(":").append( QString::number(socket.remote_endpoint().port())).append(")"))
    { }

    NetworkConnection::~NetworkConnection(){
            socket_.close();
            std::cout << "Delete NetworkConnection" << std::endl;
    }

    void NetworkConnection::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred) { }

    void NetworkConnection::receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {

        if ((error.value() == boost::asio::error::connection_reset) || (error.value() == boost::asio::error::eof)){
            std::cout << "Client disconnect!" << std::endl;
       //     delete this;    //Todo: Do it from outside


        /*******************************
         * Process request
         *******************************/
        } else {

            emit networkActivity( mId, QString("Received message: ").append( QString( QByteArray(buffer, bytes_transferred) ) ) );

            std::string vMessage(buffer, bytes_transferred);
            std::cout << vMessage << std::endl;
            std::vector< std::string > vMessageParts;

            boost::split( vMessageParts,
                          vMessage,
                          [](char aCharacter) { return aCharacter == 7; } );

            if(!vMessageParts[0].compare("book")){
                Library::getLibrary()->parseCommand( vMessageParts[1] );
            }

            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));


            /**************
             * Response
             **************/
            boost::asio::async_write(socket_, boost::asio::buffer(vMessage), std::bind(&NetworkConnection::writeHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        }
    }

    void NetworkConnection::start() {

        try {

            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
            emit networkActivity( mId, QString("New client connected on ").append( QString::fromUtf8(socket_.remote_endpoint().address().to_string().c_str() ) ).append(":").append( QString::number(socket_.remote_endpoint().port())) );

        } catch (std::exception& e) {
            emit networkActivity( mId, QString("Exception: ").append( QString(e.what()) ).append("\n") );
            socket_.close();
        }

    }
}
