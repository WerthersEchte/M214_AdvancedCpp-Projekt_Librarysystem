#include <ctime>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include "networkmanagement.h"


namespace library{

    void NetworkManagement::start(){
        try {
            boost::asio::spawn(io_service,
                [&](boost::asio::yield_context yield) {
                    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));
                    std::cout << "Listen on Port 8080" << std::endl;

                    for (;;) {
                        boost::system::error_code ec;
                        boost::asio::ip::tcp::socket socket(io_service);
                        acceptor.async_accept(socket, yield[ec]);
                        if (!ec) std::make_shared<library::NetworkConnection>(std::move(socket))->start();
                    }
                });

            io_service.run();

        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }

    void NetworkManagement::stop(){ }

    NetworkManagement::NetworkManagement(){}

    NetworkManagement::NetworkManagement(boost::asio::io_service& io_service) { }
}


