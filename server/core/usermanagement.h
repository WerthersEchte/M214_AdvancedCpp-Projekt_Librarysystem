#ifndef _LibraryUserManagement_
#define _LibraryUserManagement_

#include "user.h"

#include <vector>

typedef std::vector<library::User> Users;

namespace Library{

class UserManagement{

    Q_OBJECT

    static UserManagement *USERMANAGEMENT;

    Users mUsers;

    UserManagement();

public:

    static UserManagement* getUserManagement();

    User getUser();
    void addUser( const User& aUser );

};

}

#endif // _LibraryUserManagement_
