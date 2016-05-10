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

}
