#include "core/networkmanagement.h"
#include "gui/librarymaingui.h"

#include <QApplication>

#include <iostream>

#include "core/library.h"
#include "core/book.h"

int main(int argc, char* argv[]) {

     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 12" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 13" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 14" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
     library::Library::getLibrary()->addBook( library::Book( "test 1" ) );
    std::cout << library::Library::getLibrary()->getNumberOfBooks() << std::endl;
    std::cout << library::Library::getLibrary()->getBook(3)->getTitle() << std::endl;

	QApplication app(argc, argv);
    library::MainGUI vMainGUI;
    vMainGUI.show();
    return app.exec();

}
