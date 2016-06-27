#ifndef _LibraryLibrary_
#define _LibraryLibrary_

#include "book.h"

#include <map>
#include <vector>
#include <QObject>

typedef std::map<int,library::Book> StoredBooks;

namespace library{

class Library: public QObject{

    Q_OBJECT

    static Library *LIBRARY;

    StoredBooks mLibrary;

    Library();

public:

    static Library* getLibrary();

    int addBook( const Book& aBook );
    Book* getBook( int aId );

    int getNumberOfBooks() const;

    // parse commands

    std::string parseCommand( const std::string& aUser, const std::string& aCommand );

    void printLibrary() const;

signals:
    void changed( int vIndex );
    void libraryActivity( QString aActivity );
};

}

#endif // _LibraryLibrary_
