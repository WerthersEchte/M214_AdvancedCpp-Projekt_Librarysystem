#include <ctime>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include "networkmanagement.h"
#include <thread>
#include <memory>
#include <QMetaType>


namespace library{

    void  NetworkManagement::acceptHandler(const boost::system::error_code& error) {
        std::cout << error << std::endl;
        std::shared_ptr<library::NetworkConnection> client(new library::NetworkConnection(boost::move(socket)));

        connect(client.get(), SIGNAL(networkActivity(QString, QString)), this, SLOT(clientNetworkActivity(QString, QString)));

        socket = boost::asio::ip::tcp::socket(io_service);
        client->start();
        std::cout << "New client connect" << std::endl;
        acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));
    }



    void NetworkManagement::startServer(){

        mRuns = true;
        start();

    }

    void NetworkManagement::stopServer(){

        mRuns = false;
        io_service.stop();

    }

    NetworkManagement::NetworkManagement( const int aPort ) :
        mRuns(false),
        socket(boost::asio::ip::tcp::socket(io_service)),
        acceptor( boost::asio::ip::tcp::acceptor(
                        io_service,
                        boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(),
                                aPort)
                        )
        )
    {
    }

    void NetworkManagement::run() {
        try {

            emit networkActivity( "Main", QString("Started listen on Port ").append( QString::number( acceptor.local_endpoint().port() ) ) );
            acceptor.async_accept(socket, bind(&NetworkManagement::acceptHandler, this, std::placeholders::_1));

            while(mRuns) {
                io_service.run();
            }

            emit networkActivity( QString("Main"), QString("Stopped listen on Port ").append( QString::number( acceptor.local_endpoint().port() ) ) ) ;

        } catch (std::exception& e) {
            emit networkActivity( "Main", QString("Exception: ").append( QString(e.what()) ).append("\n") );
        }
    }

    void NetworkManagement::clientNetworkActivity( QString aId, QString aActivity ){

        emit networkActivity( aId, aActivity );

    };
}


