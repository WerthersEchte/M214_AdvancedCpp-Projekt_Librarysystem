#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#include "core/book.h"

BOOST_AUTO_TEST_CASE( Book_test_getName ) {
    std::string vTestTitle = "Die Abenteuer von Wurstmann";
    library::Book vBook( vTestTitle );
    BOOST_CHECK_EQUAL( vTestTitle, vBook.getName() );
}

