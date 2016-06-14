#include "library.h"

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

}
