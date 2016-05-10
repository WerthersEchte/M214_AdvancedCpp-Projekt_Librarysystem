#include "librarymaingui.h"

#include "add+editbook.h"
#include "libraryviewmodel.h"

#include "core/library.h"
#include "core/book.h"

#include <iostream>

namespace library{

MainGUI::MainGUI( QWidget *vParent )
    : QMainWindow(vParent)
{
    setupUi(this);

    connect(pBBooksAdd, SIGNAL(clicked(bool)), this, SLOT(addBook(bool)));
    connect(pBBooksEdit, SIGNAL(clicked(bool)), this, SLOT(editBook(bool)));
    connect(lVBooksList, SIGNAL(clicked(QModelIndex)), this, SLOT(selectBook(QModelIndex)));

    lVBooksList->setModel(new LibraryViewModel(this));
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

}

