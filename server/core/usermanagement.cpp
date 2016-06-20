#include "usermanagement.h"

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

bool UserManagement::addUser( const library::User& aUser ){

    if( mUsers.find( aUser.getUserName() ) == mUsers.end() )
    {
        mUsers[aUser.getUserName()] = aUser;
        return true;
    }
    return false;
}

}
