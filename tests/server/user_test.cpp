#include <boost/test/unit_test.hpp>
#include "core/user.h"
#include "definitions.h"


struct UserFixture {
	UserFixture() { mTestName = "Der Wurstmann";
                    mTestPassword = "Das Password";
                    mNoPermissions = {};
                    mSomePermissions = {library::Permission::Books};
                    mAllPermissions = {library::Permission::Books, library::Permission::Users}; }
	~UserFixture() {}
	std::string mTestName, mTestPassword;
	std::vector<library::Permission> mNoPermissions, mSomePermissions, mAllPermissions;
};

BOOST_FIXTURE_TEST_SUITE( UserTests, UserFixture )

    BOOST_AUTO_TEST_CASE( User_test_borrowed_books ) {
        int vFirstBookid = 1, vSecondBookId = 2, vUnknownBookId = 100;
        std::vector<int> vBorrowedBooks;
        library::User vUser( mTestName, mTestPassword, mNoPermissions );

        BOOST_TEST_CHECKPOINT( "New User - checking borrowed books" );
        BOOST_CHECK( vUser.getBorrowedBooks().empty() );
        BOOST_TEST_CHECKPOINT( "borrow 1st book" );
        vUser.addBorrowedBook( vFirstBookid );
        vBorrowedBooks = vUser.getBorrowedBooks();
        BOOST_CHECK_EQUAL( vBorrowedBooks.size(), 1 );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vFirstBookid) != vBorrowedBooks.end() );
        BOOST_TEST_CHECKPOINT( "borrow 2nd book" );
        vUser.addBorrowedBook( vSecondBookId );
        vBorrowedBooks = vUser.getBorrowedBooks();
        BOOST_CHECK_EQUAL( vBorrowedBooks.size(), 2 );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vFirstBookid) != vBorrowedBooks.end() );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vSecondBookId) != vBorrowedBooks.end() );
        BOOST_TEST_CHECKPOINT( "return 1st book" );
        vUser.removeBorrowedBook( vFirstBookid );
        vBorrowedBooks = vUser.getBorrowedBooks();
        BOOST_CHECK_EQUAL( vBorrowedBooks.size(), 1 );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vFirstBookid) == vBorrowedBooks.end() );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vSecondBookId) != vBorrowedBooks.end() );
        BOOST_TEST_CHECKPOINT( "return unknown book" );
        vUser.removeBorrowedBook( vUnknownBookId );
        vBorrowedBooks = vUser.getBorrowedBooks();
        BOOST_CHECK_EQUAL( vBorrowedBooks.size(), 1 );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vFirstBookid) == vBorrowedBooks.end() );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vSecondBookId) != vBorrowedBooks.end() );
        BOOST_TEST_CHECKPOINT( "return 2nd book" );
        vUser.removeBorrowedBook( vSecondBookId );
        vBorrowedBooks = vUser.getBorrowedBooks();
        BOOST_CHECK( vBorrowedBooks.empty() );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vFirstBookid) == vBorrowedBooks.end() );
        BOOST_CHECK( std::find(vBorrowedBooks.begin(), vBorrowedBooks.end(), vSecondBookId) == vBorrowedBooks.end() );

    }

    BOOST_AUTO_TEST_CASE( User_test_permissions ) {
        library::User vUser( mTestName, mTestPassword, mAllPermissions );
        BOOST_TEST_CHECKPOINT( "New User - checking Permissions" );
        BOOST_CHECK( vUser.hasPermission( library::Permission::Books ) );
        BOOST_CHECK( vUser.hasPermission( library::Permission::Users ) );
        BOOST_TEST_CHECKPOINT( "removing permission" );
        vUser.removePermission( library::Permission::Users );
        BOOST_CHECK( vUser.hasPermission( library::Permission::Books ) );
        BOOST_CHECK( !vUser.hasPermission( library::Permission::Users ) );
        BOOST_TEST_CHECKPOINT( "adding permission" );
        vUser.addPermission( library::Permission::Users );
        BOOST_CHECK( vUser.hasPermission( library::Permission::Books ) );
        BOOST_CHECK( vUser.hasPermission( library::Permission::Users ) );
    }

    BOOST_AUTO_TEST_CASE( User_test_getID_unique ) {
        library::User vUser1( "first book", "", mNoPermissions ), vUser2( "second book", "", mNoPermissions );
        BOOST_CHECK( vUser1.getId() != vUser2.getId() );
    }

    BOOST_AUTO_TEST_CASE( User_test_printUser ) {
        library::User vUser( mTestName, mTestPassword, mAllPermissions );
        BOOST_TEST_CHECKPOINT( "Checking for Username" );
        BOOST_CHECK( vUser.printUser().find(mTestName) != std::string::npos );
        BOOST_TEST_CHECKPOINT( "Checking for Password" );
        BOOST_CHECK( vUser.printUser().find(mTestPassword) != std::string::npos );
        BOOST_TEST_CHECKPOINT( "Checking for Permissions" );
        BOOST_CHECK( vUser.printUser().find("Permissions") != std::string::npos );
        BOOST_CHECK( vUser.printUser().find("Books") != std::string::npos );
        BOOST_CHECK( vUser.printUser().find("Users") != std::string::npos );
    }

    // getter testing againt stupid errors
    BOOST_AUTO_TEST_CASE( User_test_getUserName ) {
        library::User vUser( mTestName, mTestPassword, mNoPermissions );
        BOOST_CHECK_EQUAL( mTestName, vUser.getUserName() );
    }

    BOOST_AUTO_TEST_CASE( User_test_getPassword ) {
        library::User vUser( mTestName, mTestPassword, mNoPermissions );
        BOOST_CHECK_EQUAL( mTestPassword, vUser.getPassword() );
    }

BOOST_AUTO_TEST_SUITE_END()




