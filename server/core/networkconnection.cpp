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
#include "core/usermanagement.h"
#include "core/user.h"

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) :
        socket_(boost::move(socket)),
        mId(QString("UnkownUser(").append( QString::fromUtf8(socket.remote_endpoint().address().to_string().c_str() ) ).append(":").append( QString::number(socket.remote_endpoint().port())).append(")")),
        mUser()
    { }

    NetworkConnection::~NetworkConnection(){
            socket_.close();
            emit networkActivity( mId, QString("Client closed") );
            // TODO: disconnect all slots
    }

    void NetworkConnection::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred) { }

    void NetworkConnection::receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {

        if ((error.value() == boost::asio::error::connection_reset) || (error.value() == boost::asio::error::eof)){
            emit networkActivity( mId, QString("Disconnected") );
        } else {

            emit networkActivity( mId, QString("Received message: ").append( QString( QByteArray(buffer, bytes_transferred) ) ) );

            std::string vMessage(buffer, bytes_transferred);
            try {
                std::vector< std::string > vMessageParts;

                boost::split( vMessageParts,
                              vMessage,
                              [](char aCharacter) { return aCharacter == static_cast<char>(Splitter::TYPE); } );

                if( mUser.isEmpty() ){

                    if( vMessageParts.size() >= 2 && !vMessageParts[0].compare("login") ){
                        boost::split(   vMessageParts,
                                        vMessageParts[1],
                                        [](char aCharacter) { return aCharacter == static_cast<char>(Splitter::COMMAND); } );
                        if( UserManagement::getUserManagement()->getUser( vMessageParts[0] ) != nullptr && !UserManagement::getUserManagement()->getUser( vMessageParts[0] )->getPassword().compare(vMessageParts.size() >= 2?vMessageParts[1]:"") ){
                            mUser = QString( vMessageParts[0].c_str() );
                            mId = mUser + QString("(").append( QString::fromUtf8(socket_.remote_endpoint().address().to_string().c_str() ) ).append(":").append( QString::number(socket_.remote_endpoint().port())).append(")");
                            emit networkActivity( mId, mUser + QString(" logged in") );
                            vMessage = "logged in";
                        } else {
                            vMessage = "not logged in, wrong username or password";
                            emit networkActivity( mId, QString("User tried to log in") );
                        }

                    } else {
                        vMessage = "need to login to use library";
                    }


                } else {

                    if(!vMessageParts[0].compare("book")){
                        vMessage = Library::getLibrary()->parseCommand( mUser.toStdString(), vMessageParts[1] );
                    } else if(!vMessageParts[0].compare("user")){
                        vMessage = UserManagement::getUserManagement()->parseCommand( mUser.toStdString(), vMessageParts[1] );
                    } else if(!vMessageParts[0].compare("logout")){
                        boost::asio::async_write(socket_, boost::asio::buffer("logged out"), std::bind(&NetworkConnection::writeHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
                        return;
                    } else {
                        vMessage = "need to send valid command to interact with library";
                    }

                }
            } catch( std::exception vException ){
                vMessage = "error parsing command";
                std::cout << vException.what() << std::endl;
                emit networkActivity( mId, QString("Exception: ").append( QString(vException.what()) ) );
            }

            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
            boost::asio::async_write(socket_, boost::asio::buffer(vMessage), std::bind(&NetworkConnection::writeHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        }
    }

    void NetworkConnection::start() {

        try {

            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
            emit networkActivity( mId, QString("New client connected on ").append( QString::fromUtf8(socket_.remote_endpoint().address().to_string().c_str() ) ).append(":").append( QString::number(socket_.remote_endpoint().port())) );

        } catch (std::exception& e) {
            emit networkActivity( mId, QString("Exception: ").append( QString(e.what()) ) );
            socket_.close();
        }

    }
}
