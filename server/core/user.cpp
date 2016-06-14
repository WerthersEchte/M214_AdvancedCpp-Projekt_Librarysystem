#include "user.h"

#include <iostream>
#include <algorithm>

namespace library{

int User::IDCOUNTER = 0;

User::User() :
    mId(-1),
    mUserName(""),
    mPassword(""),
    mPermissions()
{};

User::User( std::string aUserName, std::string aPassword, const std::vector<Permission>& aPermissions ) :
    mId(IDCOUNTER++),
    mUserName(aUserName),
    mPassword(aPassword),
    mPermissions(aPermissions)
{
};

User::~User()
{};

std::string User::getUserName(){
    return mUserName;
};
void User::editUserName( std::string aUserName ){
    mUserName = aUserName;
};
std::string User::getPassword(){
    return mPassword;
};
void User::editPassword( std::string aPassword ){
    mPassword = aPassword;
};

bool User::hasPermission( Permission aPermission ){
    return std::find(mPermissions.begin(), mPermissions.end(), aPermission) != mPermissions.end();
};
void User::addPermission( Permission aPermission ){
    if( !hasPermission(aPermission) ){
        mPermissions.push_back(aPermission);
    }
};
void User::removePermission( Permission aPermission ){
    std::vector<Permission>::iterator it;
    if( (it = std::find(mPermissions.begin(), mPermissions.end(), aPermission)) != mPermissions.end() ){
        mPermissions.erase(it);
    }
};

}
