#include "usermanagement.h"

#include "definitions.h"
#include "core/library.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <sstream>

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

        if( !vCommandParts[0].compare(command::user::BURROWEDBOOKS) ){

            std::stringstream vBooks;

            for( int vBookId : getUser(aUser)->getBorrowedBooks() ){

                if( Library::getLibrary()->getBook(vBookId) != nullptr ){
                    vBooks << Library::getLibrary()->getBook(vBookId)->printBook();
                }
            }

            return vBooks.str();
        }

    } else if( vCommandParts.size() > 1 ){

        if( getUser(aUser)->hasPermission(Permission::Users) && !vCommandParts[0].compare(command::user::ADD) ){

            std::vector<Permission> mPermissions;

            for(int vI = 3; vI < vCommandParts.size(); ++vI){

                if( !vCommandParts[vI].compare("Books") ){
                    mPermissions.push_back(Permission::Books);
                } else if( !vCommandParts[vI].compare("Users") ){
                    mPermissions.push_back(Permission::Users);
                }

            }

            if( addUser( User(vCommandParts[1], vCommandParts.size() >= 3?vCommandParts[2]:"", mPermissions) ) ){
                return std::string("added user to library");
            } else {
                return std::string("can not add user to library");
            }

        } else if( getUser(aUser)->hasPermission(Permission::Users) && !vCommandParts[0].compare(command::user::CHANGEPASSWORD) ){

            if( getUser(vCommandParts[1]) != nullptr ){
                getUser(vCommandParts[1])->editPassword(vCommandParts.size() >= 3?vCommandParts[2]:"");
                return std::string("edited password");
            } else {
                return std::string("unknown user to changepassword");
            }

        } else if( getUser(aUser)->hasPermission(Permission::Users) && !vCommandParts[0].compare(command::user::GET) ){

            std::stringstream vUsers;

            if( !vCommandParts[1].compare("") ){

                for( UserMap::iterator it = mUsers.begin(); it != mUsers.end(); ++it ) {
                    vUsers << it->second.printUser();
                }

                return vUsers.str();
            }

            for( int vI = 1; vI < vCommandParts.size(); ++vI ){
                if( getUser(vCommandParts[vI]) != nullptr ){
                    vUsers << getUser(vCommandParts[vI])->printUser();
                } else {
                    vUsers << "unknown user: " << vCommandParts[vI] << "\n";
                }
            }

            return vUsers.str();

        }

    }


    return std::string("unknown command");

};

}
