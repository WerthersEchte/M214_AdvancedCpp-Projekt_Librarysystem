#include "book.h"

namespace library{

int Book::IDCOUNTER = 0;

Book::Book() :
    mId(-1),
    mName(""),
    mBurrowed(false)
{};

Book::Book( std::string aName ) :
    mId(IDCOUNTER++),
    mName(aName),
    mBurrowed(false)
{};

Book::~Book()
{};

std::string Book::getName()
{
    return mName;
};

int Book::getId()
{
    return mId;
};

bool Book::isAvailable()
{
    return !mBurrowed;
};

bool Book::burrow()
{
    if(!mBurrowed){
       mBurrowed = true;
       return true;
    }
    return false;
};

bool Book::bringBack()
{
    if(mBurrowed){
       mBurrowed = false;
       return true;
    }
    return false;
};

}
