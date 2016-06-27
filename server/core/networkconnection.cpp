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
#include "core/library.h"
#include "core/usermanagement.h"


namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) :
        mId(QString("UnkownUser(").append( QString::fromUtf8(socket.remote_endpoint().address().to_string().c_str() ) ).append(":").append( QString::number(socket.remote_endpoint().port())).append(")")),
        mUser(),
        socket_(boost::move(socket)),
        buffer()
    { }



    NetworkConnection::~NetworkConnection(){
            socket_.close();
            emit networkActivity( mId, QString("Client closed") );
            // TODO: disconnect all slots
    }



    void NetworkConnection::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred) { }



    void NetworkConnection::receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {

        if ((error.value() == boost::asio::error::connection_reset) || (error.value() == boost::asio::error::eof)) {
            emit networkActivity( mId, QString("Disconnected") );

        } else {
            emit networkActivity(mId, QString("Received message: ").append(QString(QByteArray(buffer, bytes_transferred))));
            std::string vMessage(buffer, bytes_transferred);
            std::string responseMessage;

            try {
                std::vector< std::string > vMessageParts;
                boost::split( vMessageParts,
                              vMessage,
                              [](char aCharacter) { return aCharacter == static_cast<char>(Splitter::TYPE); } );

                if( mUser.isEmpty() ){
                    if( vMessageParts.size() >= 2 && !vMessageParts[0].compare(command::LOGIN) ){
                        boost::split(   vMessageParts,
                                        vMessageParts[1],
                                        [](char aCharacter) { return aCharacter == static_cast<char>(Splitter::COMMAND); } );

                        if( UserManagement::getUserManagement()->getUser( vMessageParts[0] ) != nullptr && !UserManagement::getUserManagement()->getUser( vMessageParts[0] )->getPassword().compare(vMessageParts.size() >= 2?vMessageParts[1]:"") ){
                            mUser = QString( vMessageParts[0].c_str() );
                            mId = mUser + QString("(").append( QString::fromUtf8(socket_.remote_endpoint().address().to_string().c_str() ) ).append(":").append( QString::number(socket_.remote_endpoint().port())).append(")");
                            emit networkActivity( mId, mUser + QString(" logged in") );
							responseMessage = command::LOGIN;
							responseMessage.append(1, static_cast<char>(Splitter::TYPE));
							responseMessage.append("true");//vMessage = "logged in";

                        } else {
							responseMessage = command::LOGIN;
							responseMessage.append(1, static_cast<char>(Splitter::TYPE));
							responseMessage.append("false");//vMessage = "not logged in, wrong username or password";
                            emit networkActivity( mId, QString("User tried to log in") );
                        }

                    } else {
                        vMessage = "need to login to use library";
                    }


                } else {

                    if(!vMessageParts[0].compare(command::BOOK)) {
						responseMessage = command::BOOK;
						responseMessage.append(1, static_cast<char>(Splitter::TYPE));
						responseMessage.append(Library::getLibrary()->parseCommand( mUser.toStdString(), vMessageParts[1]));

                    } else if(!vMessageParts[0].compare(command::USER)) {
						responseMessage = command::USER;
						responseMessage.append(1, static_cast<char>(Splitter::TYPE));
						responseMessage.append(UserManagement::getUserManagement()->parseCommand( mUser.toStdString(), vMessageParts[1] ));

                    } else if(!vMessageParts[0].compare(command::LOGOUT)) {
						responseMessage = command::LOGOUT;
						responseMessage.append(1, 7);
                        boost::asio::async_write(socket_, boost::asio::buffer(responseMessage), std::bind(&NetworkConnection::writeHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
                        return; //Return without rebind the receive handler

                    } else {
						responseMessage = "error:need to send valid command to interact with library";
                    }
                }

            } catch(std::exception vException) {
				responseMessage = "error:Error parsing command";
                std::cout << vException.what() << std::endl;
                emit networkActivity( mId, QString("Exception: ").append( QString(vException.what()) ) );
            }
			responseMessage.append(1, 7);
            socket_.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
            boost::asio::async_write(socket_, boost::asio::buffer(responseMessage), std::bind(&NetworkConnection::writeHandler, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
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
