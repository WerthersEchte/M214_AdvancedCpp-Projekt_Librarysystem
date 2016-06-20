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

User::User( const User& aUser ):
    mId(aUser.mId),
    mUserName(aUser.mUserName),
    mPassword(aUser.mPassword),
    mPermissions(aUser.mPermissions)
{

    std::cout << mId << " " << mUserName << " " << mPassword << " " << std::endl;

};

User::User( User&& aUser ):
    mId(aUser.mId),
    mUserName(aUser.mUserName),
    mPassword(aUser.mPassword),
    mPermissions(aUser.mPermissions)
{
    aUser.mId = -1;
    aUser.mUserName.clear();
    aUser.mPassword.clear();
    aUser.mPermissions.clear();
};

User::~User()
{};

int User::getId(){

    return mId;

};
std::string User::getUserName(){
    return mUserName;
};
std::string User::getUserName() const{
    return mUserName;
};
void User::editUserName( std::string aUserName ){
    mUserName = aUserName;
    emit changed(mUserName.c_str());
};
std::string User::getPassword(){
    return mPassword;
};
std::string User::getPassword() const{
    return mPassword;
};
void User::editPassword( std::string aPassword ){
    mPassword = aPassword;
    emit changed(mUserName.c_str());
};

bool User::hasPermission( Permission aPermission ){
    return std::find(mPermissions.begin(), mPermissions.end(), aPermission) != mPermissions.end();
};
void User::addPermission( Permission aPermission ){
    if( !hasPermission(aPermission) ){
        mPermissions.push_back(aPermission);
        emit changed(mUserName.c_str());
    }
};
void User::removePermission( Permission aPermission ){
    std::vector<Permission>::iterator it;
    if( (it = std::find(mPermissions.begin(), mPermissions.end(), aPermission)) != mPermissions.end() ){
        mPermissions.erase(it);
        emit changed(mUserName.c_str());
    }
};

}
