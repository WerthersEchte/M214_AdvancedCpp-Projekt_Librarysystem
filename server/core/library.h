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

    bool addBook( Book aBook );
    Book* getBook( int aId );

    int getNumberOfBooks();

    //TODO: add search
    std::vector<Book> searchBooks( std::string aTitle, Status aStatus );

    // parse commands

    std::string parseCommand( const std::string& aCommand );

    void printLibrary();

signals:
    void changed( int vIndex );

private:
    std::vector<Book> searchTitle( std::string aTitle, const std::vector<Book>& aBooks );
    std::vector<Book> searchBurrowed( Status aBurrowed, const std::vector<Book>& aBooks );

};

}

#endif // _LibraryLibrary_
