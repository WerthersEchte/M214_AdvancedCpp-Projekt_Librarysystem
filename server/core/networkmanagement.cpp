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

        std::cout << error << std::endl;
        library::NetworkConnection *client = new library::NetworkConnection(boost::move(socket),  library); //TODO: Save client pointer
        socket = boost::asio::ip::tcp::socket(io_service);
        client->start();
        std::cout << "New client connect" << std::endl;
        acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));
    }

    void NetworkManagement::run(){
        try {
            std::cout << "Listen on Port 8080" << std::endl;
            acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));
            while (!stopManager) {
                io_service.run();
            }

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }

    void NetworkManagement::stop(){ }

    NetworkManagement::NetworkManagement(library::Library* _library) : socket(boost::asio::ip::tcp::socket(io_service)),
                                                                      acceptor(boost::asio::ip::tcp::acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080))),
                                                                      stopManager(false),
                                                                      library(_library){ }

}


