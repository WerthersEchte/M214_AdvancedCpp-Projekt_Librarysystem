//#define BOOST_TEST_MODULE ServerBookTest
#include <boost/test/unit_test.hpp>
#include "core/book.h"

#include <string>

struct BookFixture {
    BookFixture() { mTestTitle = "Die Abenteuer von Wurstmann";
                    mTestAuthor = "Wurstmann";
                    mTestPublisher = "Wurstmanns Macher";
                    mTestISBN = "00001010101";
                    mTestDate = "Never"; }
    ~BookFixture() {}
    std::string mTestTitle, mTestAuthor, mTestPublisher, mTestISBN, mTestDate;
};

BOOST_AUTO_TEST_SUITE( BookTests )

BOOST_AUTO_TEST_CASE( Book_test_rent ) {
    library::Book vBook( vBookFixture.mTestTitle );
    BOOST_TEST_CHECKPOINT( "New Book" );
    BOOST_CHECK_EQUAL( vBook.getStatus(), library::Status::Available );
    BOOST_TEST_CHECKPOINT( "isAvailable" );
    BOOST_CHECK( vBook.isAvailable() );
    BOOST_TEST_CHECKPOINT( "borrow Book" );
    vBook.burrow();
    BOOST_CHECK_EQUAL( vBook.getStatus(), library::Status::Burrowed );
    BOOST_TEST_CHECKPOINT( "isAvailable" );
    BOOST_CHECK( !vBook.isAvailable() );
    BOOST_TEST_CHECKPOINT( "return Book" );
    vBook.bringBack();
    BOOST_CHECK_EQUAL( vBook.getStatus(), library::Status::Available );
    BOOST_TEST_CHECKPOINT( "isAvailable" );
    BOOST_CHECK( vBook.isAvailable() );
}



BOOST_AUTO_TEST_CASE( Book_test_getID_unique ) {
    library::Book vBook1( "first book" ), vBook2( "second book" );
    BOOST_CHECK( vBook1.getId() != vBook2.getId() );
}

BOOST_AUTO_TEST_CASE( Book_test_printBook ) {
    BookFixture vBookFixture;
    library::Book vBook( vBookFixture.mTestTitle, vBookFixture.mTestAuthor, vBookFixture.mTestPublisher, vBookFixture.mTestISBN, vBookFixture.mTestDate );
    BOOST_TEST_CHECKPOINT( "Checking for Title" );
    BOOST_CHECK( vBook.printBook().find(vBookFixture.mTestTitle) != std::string::npos );
    BOOST_TEST_CHECKPOINT( "Checking for Author" );
    BOOST_CHECK( vBook.printBook().find(vBookFixture.mTestAuthor) != std::string::npos );
    BOOST_TEST_CHECKPOINT( "Checking for Publisher" );
    BOOST_CHECK( vBook.printBook().find(vBookFixture.mTestPublisher) != std::string::npos );
    BOOST_TEST_CHECKPOINT( "Checking for ISBN" );
    BOOST_CHECK( vBook.printBook().find(vBookFixture.mTestISBN) != std::string::npos );
    BOOST_TEST_CHECKPOINT( "Checking for Date" );
    BOOST_CHECK( vBook.printBook().find(vBookFixture.mTestDate) != std::string::npos );
}

// getter testing againt stupid errors
BOOST_AUTO_TEST_CASE( Book_test_getTitle ) {
    BookFixture vBookFixture;
    library::Book vBook( vBookFixture.mTestTitle );
    BOOST_CHECK_EQUAL( vBookFixture.mTestTitle, vBook.getTitle() );
}

BOOST_AUTO_TEST_CASE( Book_test_getAuthor ) {
    BookFixture vBookFixture;
    library::Book vBook( vBookFixture.mTestTitle, vBookFixture.mTestAuthor );
    BOOST_CHECK_EQUAL( vBookFixture.mTestAuthor, vBook.getAuthor() );
}

BOOST_AUTO_TEST_CASE( Book_test_getPublisher ) {
    BookFixture vBookFixture;
    library::Book vBook( vBookFixture.mTestTitle, vBookFixture.mTestAuthor, vBookFixture.mTestPublisher );
    BOOST_CHECK_EQUAL( vBookFixture.mTestPublisher, vBook.getPublisher() );
}

BOOST_AUTO_TEST_CASE( Book_test_getISBN ) {
    BookFixture vBookFixture;
    library::Book vBook( vBookFixture.mTestTitle, vBookFixture.mTestAuthor, vBookFixture.mTestPublisher, vBookFixture.mTestISBN );
    BOOST_CHECK_EQUAL( vBookFixture.mTestISBN, vBook.getISBN() );
}

BOOST_AUTO_TEST_CASE( Book_test_getDate ) {
    BookFixture vBookFixture;
    library::Book vBook( vBookFixture.mTestTitle, vBookFixture.mTestAuthor, vBookFixture.mTestPublisher, vBookFixture.mTestISBN, vBookFixture.mTestDate );
    BOOST_CHECK_EQUAL( vBookFixture.mTestDate, vBook.getDatePublished() );
}

BOOST_AUTO_TEST_SUITE_END()




