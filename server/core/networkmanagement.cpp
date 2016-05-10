#include <ctime>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include "networkmanagement.h"
#include <thread>

namespace library{

    void  NetworkManagement::acceptHandler(const boost::system::error_code& error) {
        library::NetworkConnection *client = new library::NetworkConnection(boost::move(socket));
        socket = boost::asio::ip::tcp::socket(io_service);
        client->start();
        acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));
    }



    void NetworkManagement::start(){

        try {

            std::cout << "Listen on Port " << acceptor.local_endpoint().port() << std::endl;
            acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));

            for (;;) {
                io_service.run();
            }

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }

    void NetworkManagement::stop(){ }

    NetworkManagement::NetworkManagement( const int aPort ) :
        socket(boost::asio::ip::tcp::socket(io_service)),
        acceptor( boost::asio::ip::tcp::acceptor(
                        io_service,
                        boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(),
                                aPort)
                        )
        )
    {
    }

}


