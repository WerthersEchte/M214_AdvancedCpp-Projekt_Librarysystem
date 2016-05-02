#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include "./networkconnection.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <thread>

namespace library {

    NetworkConnection::NetworkConnection(boost::asio::ip::tcp::socket socket) : socket_(boost::move(socket)) { }


    void NetworkConnection::start() {

        boost::asio::spawn(socket_.get_io_service(),
                           [&](boost::asio::yield_context yield) {
                               std::cout << "Spawn client" << std::endl;
                               try {
                                   char data[READ_DATA_BUFFER_LENGTH];

                                   for (;;) {
                                       //std::cout << "wait for msg" << std::endl;
                                       //size_t len = socket_.receive(boost::asio::buffer(data, READ_DATA_BUFFER_LENGTH);
                                               socket_.async_receive(boost::asio::buffer(data, READ_DATA_BUFFER_LENGTH), 0,
                                                                          [&](const boost::system::error_code& error, std::size_t bytes_transferred) {
                                                                              std::cout.write(data, bytes_transferred);
                                                                              std::cout << std::endl;
                                                                              boost::asio::async_write(socket_, boost::asio::buffer(data, bytes_transferred), yield);
                                                                          });

                                       //std::cout.write(data, len);
                                     //  std::cout << std::endl;
                                      // boost::asio::async_write(socket_, boost::asio::buffer(data, len), yield);
                                   }
                               }
                               catch (std::exception& e) {
                                   std::cerr << "Exception: " << e.what() << "\n";
                                   socket_.close();
                               }
                           });

        std::thread clientThread{[&](){ socket_.get_io_service().run_one(); }};
        std::cout << "Start client thread" << std::endl;
        clientThread.join();



    }
}