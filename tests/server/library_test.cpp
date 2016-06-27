//#define BOOST_TEST_MODULE ServerLibraryTest
#include <boost/test/unit_test.hpp>
#include "core/library.h"


struct LibFixture {
	LibFixture() {vTestTitle = "Die Abenteuer von Wurstmann";}
	~LibFixture() {}
	std::string vTestTitle;
};


BOOST_AUTO_TEST_SUITE( LibraryTests )

	BOOST_FIXTURE_TEST_CASE( Library_test_addBook, LibFixture) {
		library::Library* library1 = library::Library::getLibrary();
		BOOST_CHECK(library1->addBook(vTestTitle) > 0);
	}

	BOOST_FIXTURE_TEST_CASE( Library_test_getBook, LibFixture) {
		library::Library* library1 = library::Library::getLibrary();
		int bID = library1->addBook(vTestTitle);
		BOOST_CHECK_EQUAL(library1->getBook(bID)->getTitle(), vTestTitle);
	}

BOOST_AUTO_TEST_SUITE_END()




