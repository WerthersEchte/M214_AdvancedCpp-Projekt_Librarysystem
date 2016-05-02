#include <ctime>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include "networkmanagement.h"
#include <thread>

namespace library{

    void NetworkManagement::start(){

        try {
            boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));
            std::cout << "Listen on Port 8080" << std::endl;

            for (;;) {

                boost::asio::ip::tcp::socket socket(io_service);
                std::cout << "Wait for client" << std::endl;
                acceptor.accept(socket);

                std::make_shared<library::NetworkConnection>(boost::move(socket))->start();

                std::cout << "New client connect" << std::endl;
                //std::thread clientThread{[&](){ io_service.run_one(); }};
                //std::cout << "Start client thread" << std::endl;
                //clientThread.join();
             //   io_service.run();
            }

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }

    void NetworkManagement::stop(){ }

    NetworkManagement::NetworkManagement(){}

  //  NetworkManagement::NetworkManagement(boost::asio::io_service& io_service) {  }
}


