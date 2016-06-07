#include "librarymaingui.h"

#include "add+editbook.h"
#include "libraryviewmodel.h"

#include "core/library.h"
#include "core/book.h"

#include <iostream>

namespace library{

MainGUI::MainGUI( QWidget *vParent )
    : QMainWindow(vParent),
      mServer(nullptr)
{
    setupUi(this);

    pTENetworkMessages->setReadOnly(true);

    connect(pBBooksAdd, SIGNAL(clicked(bool)), this, SLOT(addBook(bool)));
    connect(pBBooksEdit, SIGNAL(clicked(bool)), this, SLOT(editBook(bool)));
    connect(lVBooksList, SIGNAL(clicked(QModelIndex)), this, SLOT(selectBook(QModelIndex)));

    lVBooksList->setModel(new LibraryViewModel(this));

    connect(bNetworkStartStop, SIGNAL(clicked(bool)), this, SLOT(networkStartStop(bool)));
};

void MainGUI::addBook( bool vChecked )
{
    AddEditBook vAddEditBookDialog;
    vAddEditBookDialog.setWindowTitle("Add Book");
    vAddEditBookDialog.exec();
    if( vAddEditBookDialog.result() == QDialog::Accepted ){

        Library::getLibrary()->addBook( Book( vAddEditBookDialog.lETitle->text().toStdString() ) );

    }
};

void MainGUI::editBook( bool vChecked )
{
    if( lVBooksList->selectionModel()->selectedIndexes().isEmpty() || Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() ) == nullptr ){
        return;
    }

    AddEditBook vAddEditBookDialog;
    vAddEditBookDialog.setWindowTitle("Edit Book");
    vAddEditBookDialog.lETitle->setText( QString::fromUtf8( Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->getTitle().c_str()) );
    vAddEditBookDialog.exec();
    if( vAddEditBookDialog.result() == QDialog::Accepted ){

        Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->editTitle( vAddEditBookDialog.lETitle->text().toStdString() );

    }

};

void MainGUI::selectBook(const QModelIndex &vIndex){

    if( Library::getLibrary()->getBook( vIndex.row() ) != nullptr ){

        lBooksId->setText( QString::number( Library::getLibrary()->getBook( vIndex.row() )->getId() ) );
        lBooksTitle->setText( QString::fromUtf8( Library::getLibrary()->getBook( vIndex.row() )->getTitle().c_str()) );
        switch(Library::getLibrary()->getBook( vIndex.row() )->getStatus() == Status::Available){
            case Available:
                lBooksStatus->setText( "Available" );
                break;
            case Burrowed:
                lBooksStatus->setText( "Burrowed" );
                break;
            default:
                lBooksStatus->setText( "Not Available" );
        }
    }

};

void MainGUI::networkStartStop( bool vChecked ){

    if( mServer == nullptr ){
        mServer = new library::NetworkManagement(lENetworkPort->text().toInt());
        connect(mServer, SIGNAL(networkActivity(QString, QString)), this, SLOT(messageNetwork(QString, QString)));

        mServer->startServer();

        bNetworkStartStop->setText("Stop");

    } else {

        mServer->stopServer();
        while(!mServer->isFinished()){} // better

        disconnect( mServer, &NetworkManagement::networkActivity, this, &MainGUI::messageNetwork );

        delete mServer; //do it with autoptr
        mServer = nullptr;

        bNetworkStartStop->setText("Start");

    }

};

void MainGUI::messageNetwork( QString aId, QString aMessage ){

    pTENetworkMessages->appendPlainText( aId.append(":").append(aMessage) );

};

}

