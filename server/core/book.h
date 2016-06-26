#ifndef _LibraryBook_
#define _LibraryBook_

#include "definitions.h"

#include <string>

namespace library{

class Book{

    static int IDCOUNTER;

    int mId;
    std::string mTitle, mISBN, mPublisher, mAuthor, mDatePublished;
    Status mBurrowed;

public:
    Book();
    Book( std::string aTitle, std::string aAuthor = "", std::string aPublisher = "", std::string aISBN = "", std::string aDatePublished = "" );
    ~Book();


    bool isAvailable();
    bool isAvailable() const;
    bool burrow();
    bool bringBack();

    Status getStatus();
    Status getStatus() const;

    int getId();
    int getId() const;

    std::string getTitle();
    std::string getTitle() const;
    void editTitle( std::string aTitle );
    std::string getAuthor();
    std::string getAuthor() const;
    void editAuthor( std::string aAuthor );
    std::string getPublisher();
    std::string getPublisher() const;
    void editPublisher( std::string aPublisher );
    std::string getISBN();
    std::string getISBN() const;
    void editISBN( std::string aISBN );
    std::string getDatePublished();
    std::string getDatePublished() const;
    void editDatePublished( std::string aPublished );

    std::string printBook( bool aEndLine = true );

};

}

#endif // _LibraryBook_
