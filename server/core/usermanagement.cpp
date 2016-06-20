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
        std::vector<Permission> vPermissions;
        USERMANAGEMENT->addUser(User("Guest", "", vPermissions ));
        vPermissions.push_back(Permission::Books);
        vPermissions.push_back(Permission::Users);
        USERMANAGEMENT->addUser(User("Admin", "Admin", vPermissions));
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

}
