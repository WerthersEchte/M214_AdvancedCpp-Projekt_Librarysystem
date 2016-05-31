#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <memory>


namespace library{

    class NetworkConnection : public std::enable_shared_from_this<NetworkConnection> {
    public:
        explicit NetworkConnection(boost::asio::ip::tcp::socket socket);
        void start();

    private:
        boost::asio::ip::tcp::socket socket_;
        void writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred);
        void receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred);
        static const int READ_DATA_BUFFER_LENGTH = 128;
        char buffer[READ_DATA_BUFFER_LENGTH];
    };
}