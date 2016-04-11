#include "book.h"

#include <map>

namespace library{

class Library{

    static Library LIBRARY;

    std::map<int,Book> mLibrary;

    Library();

public:
    
    static Library getLibrary();

    bool addBook( Book aBook );
    Book* getBook( int aId );

    //TODO: add search

};

}
