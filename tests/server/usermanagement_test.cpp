#include <boost/test/unit_test.hpp>
#include "core/usermanagement.h"

struct UserManagementFixture {
	UserManagementFixture() {}
	~UserManagementFixture() {}
    library::User mUsers[4] = { {"Admin","aaaab", {library::Permission::Books, library::Permission::Users}},
                                {"BooksAdmin","othjm", {library::Permission::Books} },
                                {"UserAdmin","ööööö", {library::Permission::Users} },
                                {"NoAdmin","rewt3", {} } };
};


BOOST_FIXTURE_TEST_SUITE( UserManagementTests, UserManagementFixture )

	BOOST_AUTO_TEST_CASE( UserManagement_test_users ) {
        BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getNumberOfUsers(), 2 );
        BOOST_TEST_CHECKPOINT( "Usermanagement - adding users" );
        for( library::User vUser : mUsers ){
            library::UserManagement::getUserManagement()->addUser( vUser );
            BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getUser(vUser.getId())->getId(), vUser.getId() );
            BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getUser(vUser.getUserName())->getId(), vUser.getId() );
        }
        BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getNumberOfUsers(), 6 );
        BOOST_TEST_CHECKPOINT( "Usermanagement - adding users again" );
        for( library::User vUser : mUsers ){
            library::UserManagement::getUserManagement()->addUser( vUser );
            BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getUser(vUser.getId())->getId(), vUser.getId() );
            BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getUser(vUser.getUserName())->getId(), vUser.getId() );
        }
        BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getNumberOfUsers(), 6 );
	}

	BOOST_AUTO_TEST_CASE( UserManagement_test_command_adduser ) {
        std::string vUserName = "TestUser",
                    vPreCommand = library::command::user::ADD + static_cast<char>(library::Splitter::COMMAND),
                    vCommand = vPreCommand + vUserName;
        int vNumberofCurrentUsers = library::UserManagement::getUserManagement()->getNumberOfUsers();

        library::UserManagement::getUserManagement()->parseCommand(mUsers[3].getUserName(), vCommand);
        BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getNumberOfUsers(), vNumberofCurrentUsers );
        library::UserManagement::getUserManagement()->parseCommand(mUsers[1].getUserName(), vCommand);
        BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getNumberOfUsers(), vNumberofCurrentUsers );
        library::UserManagement::getUserManagement()->parseCommand(mUsers[2].getUserName(), vCommand);
        BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getNumberOfUsers(), vNumberofCurrentUsers + 1 );
        library::UserManagement::getUserManagement()->parseCommand(mUsers[2].getUserName(), vCommand);
        BOOST_CHECK_EQUAL( library::UserManagement::getUserManagement()->getNumberOfUsers(), vNumberofCurrentUsers + 1 );
        BOOST_CHECK( library::UserManagement::getUserManagement()->getUser(vUserName) != nullptr );

	}


	BOOST_AUTO_TEST_CASE( UserManagement_test_command_getuser ) {
        library::User *vTestUser1 = library::UserManagement::getUserManagement()->getUser( mUsers[0].getUserName() ),
                      *vTestUser2 = library::UserManagement::getUserManagement()->getUser( mUsers[1].getUserName() );
        std::string vPreCommand = library::command::user::GET + static_cast<char>(library::Splitter::COMMAND),
                    vCommand = vPreCommand + std::to_string(vTestUser1->getId() ),
                    vResponseString = "";

        vResponseString = library::UserManagement::getUserManagement()->parseCommand(mUsers[3].getUserName(), vCommand);
        BOOST_CHECK( vResponseString.find( vTestUser1->printUser() ) == std::string::npos );
        vResponseString = library::UserManagement::getUserManagement()->parseCommand(mUsers[1].getUserName(), vCommand);
        BOOST_CHECK( vResponseString.find( vTestUser1->printUser() ) == std::string::npos );
        vResponseString = library::UserManagement::getUserManagement()->parseCommand(mUsers[2].getUserName(), vCommand);
        BOOST_CHECK( vResponseString.find( vTestUser1->printUser() ) != std::string::npos );
        vResponseString = library::UserManagement::getUserManagement()->parseCommand(mUsers[0].getUserName(), vCommand);
        BOOST_CHECK( vResponseString.find( vTestUser1->printUser() ) != std::string::npos );
        vCommand += static_cast<char>(library::Splitter::COMMAND) + std::to_string(vTestUser2->getId() );
        vResponseString = library::UserManagement::getUserManagement()->parseCommand(mUsers[0].getUserName(), vCommand);
        BOOST_CHECK( vResponseString.find( vTestUser1->printUser() ) != std::string::npos );
        BOOST_CHECK( vResponseString.find( vTestUser2->printUser() ) != std::string::npos );

	}


	BOOST_AUTO_TEST_CASE( UserManagement_test_command_changepassworduser ) {
        library::User *vTestUser1 = library::UserManagement::getUserManagement()->getUser( mUsers[0].getUserName() ),
                      *vTestUser2 = library::UserManagement::getUserManagement()->getUser( mUsers[1].getUserName() );
        std::string vPreCommand = library::command::user::CHANGEPASSWORD + static_cast<char>(library::Splitter::COMMAND),
                    vNewPassword = "Würste",
                    vCommand = vPreCommand + std::to_string(vTestUser1->getId() ) + static_cast<char>(library::Splitter::COMMAND);

        library::UserManagement::getUserManagement()->parseCommand(mUsers[3].getUserName(), vCommand + vNewPassword);
        BOOST_CHECK_EQUAL( vTestUser1->getPassword(), mUsers[0].getPassword() );
        library::UserManagement::getUserManagement()->parseCommand(mUsers[1].getUserName(), vCommand + vNewPassword);
        BOOST_CHECK_EQUAL( vTestUser1->getPassword(), mUsers[0].getPassword() );
        library::UserManagement::getUserManagement()->parseCommand(mUsers[2].getUserName(), vCommand + vNewPassword);
        BOOST_CHECK_EQUAL( vTestUser1->getPassword(), vNewPassword );
        library::UserManagement::getUserManagement()->parseCommand(mUsers[0].getUserName(), vCommand + vNewPassword + vNewPassword);
        BOOST_CHECK_EQUAL( vTestUser1->getPassword(), vNewPassword + vNewPassword );
	}

BOOST_AUTO_TEST_SUITE_END()


