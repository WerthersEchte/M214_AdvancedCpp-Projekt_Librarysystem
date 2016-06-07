#ifndef _LibraryNetworkConnection_
#define _LibraryNetworkConnection_

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>

#include <QString>

#include <iostream>
#include <memory>

#include <QObject>

#define DL "|.|"

namespace library{

    class NetworkConnection : public QObject, public std::enable_shared_from_this<NetworkConnection> {

        Q_OBJECT

        QString mId;

    public:
        explicit NetworkConnection(boost::asio::ip::tcp::socket socket);
        void start();

    signals:
        void networkActivity( QString aId, QString aActivity );

    private:
        boost::asio::ip::tcp::socket socket_;
        void writeHandler(const boost::system::error_code& error, std::size_t bytes_transferred);
        void receiveHandler(const boost::system::error_code& error, std::size_t bytes_transferred);
        static const int READ_DATA_BUFFER_LENGTH = 128;
        char buffer[READ_DATA_BUFFER_LENGTH];
    };
}

#endif //_LibraryNetworkConnection_
