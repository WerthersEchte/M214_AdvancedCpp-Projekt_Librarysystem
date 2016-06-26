#ifndef _LibraryUserManagement_
#define _LibraryUserManagement_

#include "user.h"

#include <map>
#include <string>

#include <QObject>
#include <QString>

typedef std::map<std::string, library::User> UserMap;

namespace library{

class UserManagement: public QObject{

    Q_OBJECT

    static UserManagement *USERMANAGEMENT;

    UserMap mUsers;

    UserManagement();

public:

    static UserManagement* getUserManagement();

    library::User* getUser(const std::string& mUserName);
    library::User* getUser( int aId );
    bool addUser( const library::User& aUser );

    int getNumberOfUsers() const;

    std::string parseCommand( const std::string& aUser, const std::string& aCommand );

signals:
    void userAdded( const QString& aUserName );

};

}

#endif // _LibraryUserManagement_
