#include "book.h"

#include <iostream>
#include <sstream>

namespace library{

int Book::IDCOUNTER = 0;

Book::Book() :
    mId(-1),
    mTitle(""),
    mBurrowed(Status::None)
{};

Book::Book( std::string aTitle, std::string aAuthor, std::string aPublisher, std::string aISBN, std::string aDatePublished ) :
    mId(IDCOUNTER++),
    mTitle(aTitle),
    mAuthor(aAuthor),
    mPublisher(aPublisher),
    mISBN(aISBN),
    mDatePublished(aDatePublished),
    mBurrowed(Status::Available)
{
};

Book::~Book()
{};

std::string Book::getTitle()
{
    return mTitle;
};
std::string Book::getTitle() const
{
    return getTitle();
};
void Book::editTitle( std::string aTitle )
{
    mTitle = aTitle;
};

std::string Book::getAuthor()
{
    return mAuthor;
};
std::string Book::getAuthor() const
{
    return mAuthor;
};
void Book::editAuthor( std::string aAuthor )
{
    mAuthor = aAuthor;
};

std::string Book::getPublisher()
{
    return mPublisher;
};
std::string Book::getPublisher() const
{
    return mPublisher;
};
void Book::editPublisher( std::string aPublisher )
{
    mPublisher = aPublisher;
};

std::string Book::getISBN()
{
    return mISBN;
};
std::string Book::getISBN() const
{
    return mISBN;
};
void Book::editISBN( std::string aISBN )
{
    mISBN = aISBN;
};

std::string Book::getDatePublished()
{
    return mDatePublished;
};
std::string Book::getDatePublished() const
{
    return mDatePublished;
};
void Book::editDatePublished( std::string aDatePublished )
{
    mDatePublished = aDatePublished;
};

int Book::getId()
{
    return mId;
};
int Book::getId() const
{
    return mId;
};

bool Book::isAvailable()
{
    return mBurrowed == Status::Available;
};
bool Book::isAvailable() const
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
Status Book::getStatus() const
{
    return mBurrowed;
};

std::string Book::printBook( bool aEndLine )
{
    std::stringstream vBook;
    vBook << "\"" << mId << "\",\"" << mTitle << "\",\"" << mAuthor << "\",\"" << mPublisher << "\",\"" << mDatePublished << "\",\"" << mISBN << "\",\"" << mBurrowed << "\"";
    if(aEndLine){
        vBook << std::endl;
    }
    return vBook.str();
};

}
