#ifndef _LibraryBook_
#define _LibraryBook_

#include <string>

namespace library{

enum Status{Burrowed, Available, None};

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
    bool burrow();
    bool bringBack();

    Status getStatus();

    int getId();

    std::string getTitle();
    void editTitle( std::string aTitle );
    std::string getAuthor();
    void editAuthor( std::string aAuthor );
    std::string getPublisher();
    void editPublisher( std::string aPublisher );
    std::string getISBN();
    void editISBN( std::string aISBN );
    std::string getDatePublished();
    void editDatePublished( std::string aPublished );

    void printBook();

};

}

#endif // _LibraryBook_
