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
        const int READ_DATA_BUFFER_LENGTH = 128;
    };
}