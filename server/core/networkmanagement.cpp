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
        std::shared_ptr<library::NetworkConnection> client(new library::NetworkConnection(boost::move(socket), library));
        //library::NetworkConnection *client = new library::NetworkConnection(boost::move(socket), library); //TODO: Save client pointer
        socket = boost::asio::ip::tcp::socket(io_service);
        client->start();
        std::cout << "New client connect" << std::endl;
        acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));
    }

    void NetworkManagement::run(){
        try {
            acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));

            std::thread clientThread{[&](){
                io_service.run();
                std::cout << "Stop Server thread" << std::endl;
            }};
            clientThread.detach();
            std::cout << "Start Server thread" << std::endl;
            std::cout << "Server listen on Port " << port << std::endl;

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }

    void NetworkManagement::stop(){
        io_service.stop();
     }

    NetworkManagement::NetworkManagement(std::shared_ptr<library::Library> _library, unsigned short _port) : socket(boost::asio::ip::tcp::socket(io_service)),
                                                                      acceptor(boost::asio::ip::tcp::acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port))),
                                                                      port(_port),
                                                                      library(_library){ }
}


