#include "networkconnection.h"
#include <boost/asio.hpp>

namespace library{
    class NetworkManagement{
    private:
        boost::asio::io_service io_service;
        void acceptHandler( const boost::system::error_code& error );
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::acceptor acceptor;
        unsigned short port;

    public:
        void run();
        void stop();
        NetworkManagement(unsigned short _port);
    };
}