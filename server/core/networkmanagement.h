#ifndef _LibraryNetworkManagement_
#define _LibraryNetworkManagement_

#include <boost/asio.hpp>
#include "networkconnection.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <list>

#include <QThread>
#include <QString>

namespace library{

    class NetworkManagement : public QThread{

        Q_OBJECT

        bool mRuns;
        boost::asio::io_service io_service;
        void acceptHandler( const boost::system::error_code& error );
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::acceptor acceptor;
        unsigned short port;

        void run() Q_DECL_OVERRIDE;

    public:
        NetworkManagement( const int aPort = 8080 );

        void startServer();
        void stopServer();

    signals:
        void networkActivity( QString aId, QString aActivity );

    private slots:
        void clientNetworkActivity( QString aId, QString aActivity );

    };
}

#endif //_LibraryNetworkManagement_
