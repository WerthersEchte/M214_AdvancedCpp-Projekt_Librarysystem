#include <boost/asio.hpp>
#include "networkconnection.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <list>

namespace library{

    class NetworkManagement{
    private:
        bool stopManager;
        boost::asio::io_service io_service;
    public:
        void start();
        void stop();
        NetworkManagement(boost::asio::io_service& io_service);
        NetworkManagement();

    };
}