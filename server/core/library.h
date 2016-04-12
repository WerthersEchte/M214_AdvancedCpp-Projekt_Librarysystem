#include "book.h"

#include <map>
#include <vector>

typedef std::map<int,library::Book> StoredBooks;

namespace library{

class Library{

    static Library LIBRARY;

    StoredBooks mLibrary;

    Library();

public:

    static Library getLibrary();

    bool addBook( Book aBook );
    Book* getBook( int aId );

    //TODO: add search
    std::vector<Book> searchBooks( std::string aTitle, Status aStatus );

private:
    std::vector<Book> searchTitle( std::string aTitle, const std::vector<Book>& aBooks );
    std::vector<Book> searchBurrowed( Status aBurrowed, const std::vector<Book>& aBooks );

};

}
