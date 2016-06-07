#include "librarymaingui.h"

#include "add+editbook.h"
#include "libraryviewmodel.h"

#include "core/library.h"
#include "core/book.h"

#include <iostream>
#include <fstream>

#include <QFileDialog>
#include <QMessageBox>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace library{

MainGUI::MainGUI( QWidget *vParent )
    : QMainWindow(vParent),
      mServer(nullptr)
{
    setupUi(this);

    menuBar()->show();
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

        Library::getLibrary()->addBook( Book( vAddEditBookDialog.lETitle->text().toStdString(), vAddEditBookDialog.lEAuthor->text().toStdString(), vAddEditBookDialog.lEPublisher->text().toStdString(), vAddEditBookDialog.lEISBN->text().toStdString(), vAddEditBookDialog.lEDate->text().toStdString() ) );

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
    vAddEditBookDialog.lEAuthor->setText( QString::fromUtf8( Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->getAuthor().c_str()) );
    vAddEditBookDialog.lEPublisher->setText( QString::fromUtf8( Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->getPublisher().c_str()) );
    vAddEditBookDialog.lEISBN->setText( QString::fromUtf8( Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->getISBN().c_str()) );
    vAddEditBookDialog.lEDate->setText( QString::fromUtf8( Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->getDatePublished().c_str()) );
    vAddEditBookDialog.exec();
    if( vAddEditBookDialog.result() == QDialog::Accepted ){

        Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->editTitle( vAddEditBookDialog.lETitle->text().toStdString() );
        Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->editAuthor( vAddEditBookDialog.lEAuthor->text().toStdString() );
        Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->editPublisher( vAddEditBookDialog.lEPublisher->text().toStdString() );
        Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->editISBN( vAddEditBookDialog.lEISBN->text().toStdString() );
        Library::getLibrary()->getBook( lVBooksList->selectionModel()->selectedIndexes().first().row() )->editDatePublished( vAddEditBookDialog.lEDate->text().toStdString() );

    }

};

void MainGUI::selectBook(const QModelIndex &vIndex){

    if( Library::getLibrary()->getBook( vIndex.row() ) != nullptr ){

        lBooksId->setText( QString::number( Library::getLibrary()->getBook( vIndex.row() )->getId() ) );
        lBooksTitle->setText( QString::fromUtf8( Library::getLibrary()->getBook( vIndex.row() )->getTitle().c_str()) );
        lBooksAuthor->setText( QString::fromUtf8( Library::getLibrary()->getBook( vIndex.row() )->getAuthor().c_str()) );
        lBooksPublisher->setText( QString::fromUtf8( Library::getLibrary()->getBook( vIndex.row() )->getPublisher().c_str()) );
        lBooksISBN->setText( QString::fromUtf8( Library::getLibrary()->getBook( vIndex.row() )->getISBN().c_str()) );
        lBooksDate->setText( QString::fromUtf8( Library::getLibrary()->getBook( vIndex.row() )->getDatePublished().c_str()) );

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

void MainGUI::on_actionLoad_books_triggered()
{
    std::string vModelFileName = QFileDialog::getOpenFileName(this, tr("Open Bookfile"), "", tr("All Files (*)")).toUtf8().constData();

	loadBooks( vModelFileName );
}

void MainGUI::loadBooks( std::string aFileWithBooks ){

	if ( aFileWithBooks.empty() || !QDir::isAbsolutePath( aFileWithBooks.c_str() ) ){
		return;
	}

	try{
        std::ifstream vBookFileSteam( aFileWithBooks.c_str() );

        if( vBookFileSteam.good() ){

            std::vector< std::string > vBookParts;
            std::string vBookDataString;

            while ( std::getline( vBookFileSteam, vBookDataString ) )
            {
                vBookParts.clear();
                try{

                    boost::split( vBookParts, vBookDataString, [](char aCharacter) { return aCharacter == ';'; } );
                    if(vBookParts.size() >= 12){
                        Library::getLibrary()->addBook(Book(vBookParts[1], "", vBookParts[10], vBookParts[0], vBookParts[11]));
                    }

                } catch( std::invalid_argument* vException ){
                    std::cout << vException->what() << std::endl;
                }

            }

        }
	} catch ( std::exception vEveryThing ){

		std::string aHeader("Exception loading file " + aFileWithBooks);
		QMessageBox::critical(this, tr( aHeader.c_str() ), tr( vEveryThing.what() ));

	}

}

}

