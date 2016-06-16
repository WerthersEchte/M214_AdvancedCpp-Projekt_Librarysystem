#ifndef _LibraryUserManagement_
#define _LibraryUserManagement_

#include "user.h"

#include <map>
#include <string>

typedef std::map<std::string, library::User> UserMap;

namespace library{

class UserManagement{

    static UserManagement *USERMANAGEMENT;

    UserMap mUsers;

    UserManagement();

public:

    static UserManagement* getUserManagement();

    library::User* getUser(const std::string& mUserName);
    bool addUser( const library::User& aUser );

};

}

#endif // _LibraryUserManagement_
