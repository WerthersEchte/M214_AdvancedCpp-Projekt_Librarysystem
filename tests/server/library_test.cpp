#include <boost/test/unit_test.hpp>
#include "core/library.h"
#include "core/user.h"
#include "core/usermanagement.h"

struct LibraryFixture {
    LibraryFixture() { mAdmin = library::UserManagement::getUserManagement()->getUser( "admin" );
                       mGuest = library::UserManagement::getUserManagement()->getUser( "guest" ); }
	~LibraryFixture() {}
    library::User *mAdmin, *mGuest;
};


BOOST_FIXTURE_TEST_SUITE( LibraryTests, LibraryFixture )

	BOOST_AUTO_TEST_CASE( Library_test_users ) {
        BOOST_TEST_CHECKPOINT( "Library - adding books" );
        int vNumberBefore = library::Library::getLibrary()->getNumberOfBooks();
        for( int vI = 0; vI < 5; ++vI ){
            library::Book vTestBook(" ");
            library::Library::getLibrary()->addBook(vTestBook);
            BOOST_CHECK( library::Library::getLibrary()->getBook(vTestBook.getId()) != nullptr );
        }
        BOOST_CHECK_EQUAL( vNumberBefore, library::Library::getLibrary()->getNumberOfBooks() - 5 );
	}

	BOOST_AUTO_TEST_CASE( Library_test_command_addbook ) {
        library::Book vTestBook("This is a Testbook");
        std::string vPreCommand = library::command::book::ADD + static_cast<char>(library::Splitter::COMMAND),
                    vCommand = vPreCommand + vTestBook.getTitle(),
                    vResponseMessage = "";

        vResponseMessage = library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vCommand);
        BOOST_CHECK( vResponseMessage.find( vTestBook.getTitle() ) == std::string::npos );
        vResponseMessage = library::Library::getLibrary()->parseCommand(mAdmin->getUserName(), vCommand);
        BOOST_CHECK( vResponseMessage.find( vTestBook.getTitle() ) != std::string::npos );
	}

	BOOST_AUTO_TEST_CASE( Library_test_command_get ) {
        library::Book vTestBook1("This is a Testbook"),
                      vTestBook2("This is a second Testbook");
        library::Library::getLibrary()->addBook(vTestBook1);
        library::Library::getLibrary()->addBook(vTestBook2);
        std::string vPreCommand = library::command::book::GET + static_cast<char>(library::Splitter::COMMAND),
                    vResponseMessage = "";

        vResponseMessage = library::Library::getLibrary()->parseCommand(mAdmin->getUserName(), vPreCommand + std::to_string(vTestBook1.getId()) );
        BOOST_CHECK( vResponseMessage.find( vTestBook1.printBook() ) != std::string::npos );
        vResponseMessage = library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vPreCommand + std::to_string(vTestBook1.getId()) );
        BOOST_CHECK( vResponseMessage.find( vTestBook1.printBook()  ) != std::string::npos );
        vResponseMessage = library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vPreCommand + std::to_string(-1) );
        BOOST_CHECK( vResponseMessage.find( "unknown" ) != std::string::npos );
        BOOST_CHECK( vResponseMessage.find( std::to_string(-1) ) != std::string::npos );
        vResponseMessage = library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vPreCommand + std::to_string(vTestBook1.getId()) + static_cast<char>(library::Splitter::COMMAND) + std::to_string( vTestBook2.getId() ) );
        BOOST_CHECK( vResponseMessage.find( vTestBook1.printBook()  ) != std::string::npos );
        BOOST_CHECK( vResponseMessage.find( vTestBook2.printBook()  ) != std::string::npos );
    }

	BOOST_AUTO_TEST_CASE( Library_test_command_editbook ) {
	    library::Book vTestBook("This is a Testbook");
        library::Library::getLibrary()->addBook(vTestBook);
        std::string vNewTitle = "New Title",
                    vPreCommand = library::command::book::EDIT + static_cast<char>(library::Splitter::COMMAND),
                    vCommand = vPreCommand + std::to_string(vTestBook.getId()) + static_cast<char>(library::Splitter::COMMAND) + vNewTitle;

        library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vCommand );
        BOOST_CHECK_NE( library::Library::getLibrary()->getBook(vTestBook.getId())->getTitle(), vNewTitle );
        library::Library::getLibrary()->parseCommand(mAdmin->getUserName(), vCommand );
        BOOST_CHECK_EQUAL( library::Library::getLibrary()->getBook(vTestBook.getId())->getTitle(), vNewTitle );


	}

	BOOST_AUTO_TEST_CASE( Library_test_command_return ) {

        std::vector<int> vBorrowedBooks;
	    library::Book vTestBook1("This is a Testbook");
	    vTestBook1.burrow();
	    library::Book vTestBook2("This is a Testbook");
	    vTestBook2.burrow();
	    library::Book vTestBook3("This is a Testbook");
	    vTestBook3.burrow();
        library::Library::getLibrary()->addBook(vTestBook1);
        library::Library::getLibrary()->addBook(vTestBook2);
        library::Library::getLibrary()->addBook(vTestBook3);
        mGuest->addBorrowedBook(vTestBook1.getId());
        mGuest->addBorrowedBook(vTestBook2.getId());
        mGuest->addBorrowedBook(vTestBook3.getId());

        std::string vPreCommand = library::command::book::RETURN + static_cast<char>(library::Splitter::COMMAND);

        library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vPreCommand + std::to_string(vTestBook1.getId() ) );
        BOOST_CHECK( library::Library::getLibrary()->getBook(vTestBook1.getId())->isAvailable() );
        vBorrowedBooks = mGuest->getBorrowedBooks();
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vTestBook1.getId() ) == vBorrowedBooks.end() );
        library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vPreCommand  + std::to_string(vTestBook2.getId() )  + static_cast<char>(library::Splitter::COMMAND) + std::to_string(vTestBook3.getId() ) );
        BOOST_CHECK( library::Library::getLibrary()->getBook(vTestBook2.getId())->isAvailable() );
        BOOST_CHECK( library::Library::getLibrary()->getBook(vTestBook3.getId())->isAvailable() );
        vBorrowedBooks = mGuest->getBorrowedBooks();
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vTestBook2.getId() ) == vBorrowedBooks.end() );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vTestBook3.getId() ) == vBorrowedBooks.end() );

    }

	BOOST_AUTO_TEST_CASE( Library_test_command_burrow ) {

        std::vector<int> vBorrowedBooks;
	    library::Book vTestBook1("This is a Testbook");
	    library::Book vTestBook2("This is a Testbook");
	    library::Book vTestBook3("This is a Testbook");
        library::Library::getLibrary()->addBook(vTestBook1);
        library::Library::getLibrary()->addBook(vTestBook2);
        library::Library::getLibrary()->addBook(vTestBook3);

        std::string vPreCommand = library::command::book::BURROW + static_cast<char>(library::Splitter::COMMAND);

        library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vPreCommand + std::to_string(vTestBook1.getId() ) );
        BOOST_CHECK( !library::Library::getLibrary()->getBook(vTestBook1.getId())->isAvailable() );
        vBorrowedBooks = mGuest->getBorrowedBooks();
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vTestBook1.getId() ) != vBorrowedBooks.end() );
        library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vPreCommand  + std::to_string(vTestBook2.getId() )  + static_cast<char>(library::Splitter::COMMAND) + std::to_string(vTestBook3.getId() ) );
        BOOST_CHECK( !library::Library::getLibrary()->getBook(vTestBook2.getId())->isAvailable() );
        BOOST_CHECK( !library::Library::getLibrary()->getBook(vTestBook3.getId())->isAvailable() );
        vBorrowedBooks = mGuest->getBorrowedBooks();
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vTestBook2.getId() ) != vBorrowedBooks.end() );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vTestBook3.getId() ) != vBorrowedBooks.end() );

    }

	BOOST_AUTO_TEST_CASE( Library_test_command_search ) {

	    library::Book vTestBook1("alibaba hurra");
	    library::Book vTestBook2("alibaba boo");
        library::Library::getLibrary()->addBook(vTestBook1);
        library::Library::getLibrary()->addBook(vTestBook2);

        std::string vCommand = library::command::book::SEARCH + static_cast<char>(library::Splitter::COMMAND) + "alibaba",
                    vResponse = "";

        vResponse = library::Library::getLibrary()->parseCommand(mGuest->getUserName(), vCommand );
        BOOST_CHECK( vResponse.find( vTestBook1.printBook()  ) != std::string::npos );
        BOOST_CHECK( vResponse.find( vTestBook2.printBook()  ) != std::string::npos );
    }

BOOST_AUTO_TEST_SUITE_END()


