//#define BOOST_TEST_MODULE ServerBookTest
#include <boost/test/unit_test.hpp>
#include "core/book.h"

struct BookFixture {
    BookFixture() {vTestTitle = "Die Abenteuer von Wurstmann";}
    ~BookFixture() {}
    std::string vTestTitle;
};

BOOST_AUTO_TEST_SUITE( BookTests )

// This is a bad test, as it depends on position in execution
BOOST_AUTO_TEST_CASE( Book_test_getID_bad ) {
    BookFixture bookFixture;
    library::Book vBook( bookFixture.vTestTitle );
    BOOST_CHECK_EQUAL( 0, vBook.getId() );
}

BOOST_AUTO_TEST_CASE( Book_test_getID_unique ) {
    library::Book vBook1( "first book" ), vBook2( "second book" );
    BOOST_CHECK( vBook1.getId() != vBook2.getId() );
}

BOOST_AUTO_TEST_CASE( Book_test_getName ) {
    BookFixture bookFixture;
    library::Book vBook( bookFixture.vTestTitle );
    BOOST_CHECK_EQUAL( bookFixture.vTestTitle, vBook.getTitle() );
}

BOOST_AUTO_TEST_CASE( Book_test_noTitle ) {
   std::string vTestTitle = "";
    library::Book vBook( vTestTitle );
    BOOST_CHECK( vBook.getTitle() != "" );
	//BOOST_WARN_THROW(library::Book vBook( "" ), std::exception);
    BOOST_TEST_MESSAGE("Test Message");
}

BOOST_AUTO_TEST_SUITE_END()




