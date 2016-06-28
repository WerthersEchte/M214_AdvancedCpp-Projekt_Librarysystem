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

BOOST_FIXTURE_TEST_SUITE( BookTests, BookFixture )

    BOOST_AUTO_TEST_CASE( Book_test_rent ) {
        library::Book vBook( mTestTitle );
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
        library::Book vBook( mTestTitle, mTestAuthor, mTestPublisher, mTestISBN, mTestDate );
        BOOST_TEST_CHECKPOINT( "Checking for Title" );
        BOOST_CHECK( vBook.printBook().find(mTestTitle) != std::string::npos );
        BOOST_TEST_CHECKPOINT( "Checking for Author" );
        BOOST_CHECK( vBook.printBook().find(mTestAuthor) != std::string::npos );
        BOOST_TEST_CHECKPOINT( "Checking for Publisher" );
        BOOST_CHECK( vBook.printBook().find(mTestPublisher) != std::string::npos );
        BOOST_TEST_CHECKPOINT( "Checking for ISBN" );
        BOOST_CHECK( vBook.printBook().find(mTestISBN) != std::string::npos );
        BOOST_TEST_CHECKPOINT( "Checking for Date" );
        BOOST_CHECK( vBook.printBook().find(mTestDate) != std::string::npos );
    }

    // getter testing againt stupid errors
    BOOST_AUTO_TEST_CASE( Book_test_getTitle ) {
        library::Book vBook( mTestTitle );
        BOOST_CHECK_EQUAL( mTestTitle, vBook.getTitle() );
    }

    BOOST_AUTO_TEST_CASE( Book_test_getAuthor ) {
        library::Book vBook( mTestTitle, mTestAuthor );
        BOOST_CHECK_EQUAL( mTestAuthor, vBook.getAuthor() );
    }

    BOOST_AUTO_TEST_CASE( Book_test_getPublisher ) {
        library::Book vBook( mTestTitle, mTestAuthor, mTestPublisher );
        BOOST_CHECK_EQUAL( mTestPublisher, vBook.getPublisher() );
    }

    BOOST_AUTO_TEST_CASE( Book_test_getISBN ) {
        library::Book vBook( mTestTitle, mTestAuthor, mTestPublisher, mTestISBN );
        BOOST_CHECK_EQUAL( mTestISBN, vBook.getISBN() );
    }

    BOOST_AUTO_TEST_CASE( Book_test_getDate ) {
        library::Book vBook( mTestTitle, mTestAuthor, mTestPublisher, mTestISBN, mTestDate );
        BOOST_CHECK_EQUAL( mTestDate, vBook.getDatePublished() );
    }

BOOST_AUTO_TEST_SUITE_END()




