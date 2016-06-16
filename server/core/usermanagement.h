#ifndef _LibraryUserManagement_
#define _LibraryUserManagement_

#include "user.h"

#include <vector>

typedef std::vector<library::User> UserMap;

namespace library{

class UserManagement{

    static UserManagement *USERMANAGEMENT;

    UserMap mUsers;

    UserManagement();

public:

    static UserManagement* getUserManagement();

    library::User getUser();
    void addUser( const library::User& aUser );

};

}

#endif // _LibraryUserManagement_
