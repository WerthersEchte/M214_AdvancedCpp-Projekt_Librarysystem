#ifndef _LibraryUser_
#define _LibraryUser_

#include <string>
#include <vector>

namespace library{

enum Permission{Users, Books, None};

class User{

    static int IDCOUNTER;

    int mId;
    std::string mUserName, mPassword;
    std::vector<Permission> mPermissions;

public:
    User();
    User( std::string mUserName, std::string mPassword, const std::vector<Permission>& aPermissions );
    ~User();

    std::string getUserName();
    std::string getUserName() const;
    void editUserName( std::string aUserName );
    std::string getPassword();
    std::string getPassword() const;
    void editPassword( std::string aPassword );

    bool hasPermission( Permission aPermission );
    void addPermission( Permission aPermission );
    void removePermission( Permission aPermission );

};

}

#endif // _LibraryUser_
