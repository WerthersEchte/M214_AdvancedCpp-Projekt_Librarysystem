#include "usermanagement.h"

#include "core/networkconnection.h"
#include "core/library.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace library{

UserManagement* UserManagement::USERMANAGEMENT = nullptr;

UserManagement::UserManagement() :
mUsers()
{

};

UserManagement* UserManagement::getUserManagement()
{
    if(USERMANAGEMENT == nullptr){
        USERMANAGEMENT = new UserManagement();
        std::vector<Permission> vPermissions;
        USERMANAGEMENT->addUser(User("guest", "", vPermissions ));
        vPermissions.push_back(Permission::Books);
        vPermissions.push_back(Permission::Users);
        USERMANAGEMENT->addUser(User("admin", "admin", vPermissions));
    }
    return USERMANAGEMENT;
};

library::User* UserManagement::getUser( const std::string& mUserName ){

    try{
        return &(mUsers.at(mUserName));
    } catch ( const std::out_of_range& aNotFound ) {
        return nullptr;
    }

};

library::User* UserManagement::getUser( int aId ){

    for( UserMap::iterator it = mUsers.begin(); it != mUsers.end(); ++it ) {
    	if( aId == it->second.getId() ){
            return &(it->second);
    	}
    }
    return nullptr;

};

bool UserManagement::addUser( const library::User& aUser ){

    if( mUsers.find( aUser.getUserName() ) == mUsers.end() )
    {
        mUsers.insert( std::pair<std::string, library::User>(aUser.getUserName(), aUser) );
        emit userAdded(aUser.getUserName().c_str());
        return true;
    }
    return false;
}

int UserManagement::getNumberOfUsers(){

    return mUsers.size();

};
std::string UserManagement::parseCommand( const std::string& aUser, const std::string& aCommand ){

    std::vector< std::string > vCommandParts;

    boost::split( vCommandParts,
                  aCommand,
                  [](char aCharacter) { return aCharacter == static_cast<char>(Splitter::COMMAND); } );

    if( vCommandParts.size() == 1  ){

        if( !vCommandParts[0].compare("borrowedbooks") ){

            std::stringstream vBooks;

            for( int vBookId : getUser(aUser)->getBorrowedBooks() ){

                if( Library::getLibrary()->getBook(vBookId) != nullptr ){
                    vBooks << Library::getLibrary()->getBook(vBookId)->printBook();
                }
            }

            return vBooks.str();
        }

    } else if( vCommandParts.size() > 1 ){
    }


    return std::string("unknown command");

};

}
