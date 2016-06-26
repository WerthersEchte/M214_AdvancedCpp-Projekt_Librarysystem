#ifndef _LibraryBook_
#define _LibraryBook_

#include "definitions.h"

#include <string>

namespace library{

class Book{

    static int IDCOUNTER;

    int mId;
    std::string mTitle, mAuthor, mPublisher, mISBN, mDatePublished;
    Status mBurrowed;

public:
    Book();
    Book( const std::string& aTitle, const std::string& aAuthor = "", const std::string& aPublisher = "", const std::string& aISBN = "", const std::string& aDatePublished = "" );
    ~Book();

    bool isAvailable() const;
    bool burrow();
    bool bringBack();

    Status getStatus() const;

    int getId() const;

    std::string getTitle() const;
    void editTitle( const std::string& aTitle );
    std::string getAuthor() const;
    void editAuthor( const std::string& aAuthor );
    std::string getPublisher() const;
    void editPublisher( const std::string& aPublisher );
    std::string getISBN() const;
    void editISBN( const std::string& aISBN );
    std::string getDatePublished() const;
    void editDatePublished( const std::string& aPublished );

    std::string printBook( bool aEndLine = true ) const;

};

}

#endif // _LibraryBook_
