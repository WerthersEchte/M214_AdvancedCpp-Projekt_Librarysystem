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

Book::Book( const std::string& aTitle, const std::string& aAuthor, const std::string& aPublisher, const std::string& aISBN, const std::string& aDatePublished ) :
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
std::string Book::getTitle() const
{
    return mTitle;
};
void Book::editTitle( const std::string& aTitle )
{
    mTitle = aTitle;
};

std::string Book::getAuthor() const
{
    return mAuthor;
};
void Book::editAuthor( const std::string& aAuthor )
{
    mAuthor = aAuthor;
};

std::string Book::getPublisher() const
{
    return mPublisher;
};
void Book::editPublisher( const std::string& aPublisher )
{
    mPublisher = aPublisher;
};

std::string Book::getISBN() const
{
    return mISBN;
};
void Book::editISBN( const std::string& aISBN )
{
    mISBN = aISBN;
};

std::string Book::getDatePublished() const
{
    return mDatePublished;
};
void Book::editDatePublished( const std::string& aDatePublished )
{
    mDatePublished = aDatePublished;
};

int Book::getId() const
{
    return mId;
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

Status Book::getStatus() const
{
    return mBurrowed;
};

std::string Book::printBook( bool aEndLine ) const
{
    std::stringstream vBook;
    vBook << "\"" << mId << "\",\"" << mTitle << "\",\"" << mAuthor << "\",\"" << mPublisher << "\",\"" << mDatePublished << "\",\"" << mISBN << "\",\"" << mBurrowed << "\"";
    if(aEndLine){
        vBook << std::endl;
    }
    return vBook.str();
};

}
