#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace library{

    class NetworkConnection : public std::enable_shared_from_this<NetworkConnection> {
    public:
        explicit NetworkConnection(boost::asio::ip::tcp::socket socket);
        ~NetworkConnection();
        void start();

    private:
        boost::asio::ip::tcp::socket socket;
        void writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred);
        void receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred);
        static const int READ_DATA_BUFFER_LENGTH = 128;
        char buffer[READ_DATA_BUFFER_LENGTH];
    };
}