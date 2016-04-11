#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include "core/book.h"

// This is a bad test, as it depends on position in execution
BOOST_AUTO_TEST_CASE( Book_test_getID_bad ) {
    std::string vTestTitle = "Die Abenteuer von Wurstmann";
    library::Book vBook( vTestTitle );
    BOOST_CHECK_EQUAL( 0, vBook.getId() );
}

BOOST_AUTO_TEST_CASE( Book_test_getID_unique ) {
    library::Book vBook1( "first book" ), vBook2( "second book" );
    BOOST_CHECK( vBook1.getId() != vBook2.getId() );
}

BOOST_AUTO_TEST_CASE( Book_test_getName ) {
    std::string vTestTitle = "Die Abenteuer von Wurstmann";
    library::Book vBook( vTestTitle );
    BOOST_CHECK_EQUAL( vTestTitle, vBook.getName() );
}
