#include "book.h"

namespace library{

int Book::IDCOUNTER = 0;

Book::Book() :
    mId(-1),
    mTitle(""),
    mBurrowed(Status::None)
{};

Book::Book( std::string aTitle ) :
    mId(IDCOUNTER++),
    mTitle(aTitle),
    mBurrowed(Status::Available)
{};

Book::~Book()
{};

std::string Book::getTitle()
{
    return mTitle;
};

void Book::editTitle( std::string aTitle )
{
    mTitle = aTitle;
};

int Book::getId()
{
    return mId;
};

bool Book::isAvailable()
{
    return mBurrowed == Status::Available;
};

bool Book::burrow()
{
    if( mBurrowed == Status::Available){
       mBurrowed = Status::Burrowed;
       return true;
    }
    return false;
};

bool Book::bringBack()
{
    if(mBurrowed == Status::Burrowed){
       mBurrowed = Status::Available;
       return true;
    }
    return false;
};

Status Book::getStatus()
{
    return mBurrowed;
};

}
