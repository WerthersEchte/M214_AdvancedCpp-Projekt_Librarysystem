#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include "networkconnection.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
//#include "library.h"
//#include <string>
#include <boost/algorithm/string.hpp>

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket _socket, library::Library* _library) : socket(boost::move(_socket)), library(_library)  { }

    NetworkConnection::~NetworkConnection(){
        socket.close();
        std::cout << "Delete connection object" << std::endl;
    }


    void NetworkConnection::writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred) { }

    void NetworkConnection::receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {


        /*********************************
         * Error handling
         *********************************/
        if ((error.value() == boost::asio::error::connection_reset) || (error.value() == boost::asio::error::eof)){
            std::cout << "Client disconnect!" << std::endl;
            delete this;    //Todo: Do it from outside


        /*******************************
         * Process request
         *******************************/
        } else {
            std::vector<string> vMessage;
            boost::split(vMessage, buffer, boost::is_any_of(";"));
            string responseType = vMessage.at(0);
            string returnData;

            if (responseType == "book" && vMessage.size() >= 2) {
                string responseSubType = vMessage.at(1);

                if (responseSubType == "add" && vMessage.size() >= 3) {

                    //Split message part
                    std::vector<string> vMsg;
                    boost::split(vMsg, vMessage.at(2), boost::is_any_of("#"));

                    //Add book
                    library->addBook(library::Book(std::stoi(vMsg.at(0)), vMsg.at(1)));
                    returnData = "addBook";

                } else if (responseSubType == "get"){
                    int bookID = std::stoi(vMessage.at(2));
                    returnData = library->getBook(bookID).toString().c_str();
                }

            } else {
                std::cout << "Receive unknown message: ";
                std::cout.write(buffer, bytes_transferred) << std::endl;
                returnData = "unknownMessage!";
            }
            socket.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, this, std::placeholders::_1, std::placeholders::_2));


            /**************
             * Response
             **************/
           // boost::asio::async_write(socket, boost::asio::buffer(buffer, bytes_transferred), std::bind(&NetworkConnection::writeHandler, this, std::placeholders::_1, std::placeholders::_2));
            boost::asio::async_write(socket, boost::asio::buffer(returnData, sizeof(returnData)), std::bind(&NetworkConnection::writeHandler, this, std::placeholders::_1, std::placeholders::_2));
           // boost::asio::async_write(socket, returnData, std::bind(&NetworkConnection::writeHandler, this, std::placeholders::_1, std::placeholders::_2));

        }
    }

    void NetworkConnection::start() {
        try {
            socket.async_receive(boost::asio::buffer(buffer, READ_DATA_BUFFER_LENGTH), 0, std::bind(&NetworkConnection::receiveHandler, this, std::placeholders::_1, std::placeholders::_2));

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
            socket.close();
        }

    }
}