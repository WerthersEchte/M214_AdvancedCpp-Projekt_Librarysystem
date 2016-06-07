#include "library.h"

#include <map>
#include <stdexcept>
#include <iostream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace library{

Library* Library::LIBRARY = nullptr;

Library::Library() :
mLibrary()
{

    for( char vI1 = 65; vI1 < 91; ++vI1 ){
        for( char vI2 = 97; vI2 < 123; ++vI2 ){
            for( char vI3 = 97; vI3 < 123; ++vI3 ){

                addBook( library::Book( {vI1, vI2, vI3} ) );

            }
        }
    }

};

Library* Library::getLibrary()
{
    if(LIBRARY == nullptr){
        LIBRARY = new Library();
    }
    return LIBRARY;
};

bool Library::addBook( Book aBook )
{
    if( mLibrary.find( aBook.getId() ) == mLibrary.end() )
    {
        mLibrary[aBook.getId()] = aBook;
        emit changed(aBook.getId());
        return true;
    }
    return false;
};

Book* Library::getBook( int aId )
{
    try{
        return &(mLibrary.at(aId));
    } catch ( const std::out_of_range& aNotFound ) {
        return nullptr;
    }
};

int Library::getNumberOfBooks()
{
    return mLibrary.size();
};

std::vector<Book> Library::searchBooks( std::string aTitle, Status aBurrowed )
{
    std::vector<Book> vBooks;

    for( StoredBooks::iterator it = mLibrary.begin(); it != mLibrary.end(); ++it ) {
    	vBooks.push_back( it->second );
    }

    if( !aTitle.empty() ){
        vBooks = searchTitle( aTitle, vBooks );
    }

    if( aBurrowed != Status::None ){
        vBooks = searchBurrowed( aBurrowed, vBooks );
    }

    return vBooks;
};

std::vector<Book> Library::searchTitle( std::string aTitle, const std::vector<Book>& aBooks )
{
    std::vector<Book> vFoundBooks;

    for( Book vBook : aBooks ){
        if( vBook.getTitle().find( aTitle ) != std::string::npos ){
            vFoundBooks.push_back( vBook );
        }
    }

    return vFoundBooks;
};

std::vector<Book> Library::searchBurrowed( Status aBurrowed, const std::vector<Book>& aBooks )
{
    std::vector<Book> vFoundBooks;

    for( Book vBook : aBooks ){
        if( vBook.getStatus() == aBurrowed ){
            vFoundBooks.push_back( vBook );
        }
    }

    return vFoundBooks;
};

std::string Library::parseCommand( const std::string& aCommand ){

    std::vector< std::string > vCommandParts;

    boost::split( vCommandParts,
                  aCommand,
                  [](char aCharacter) { return aCharacter == '|'; } );

    if(!vCommandParts[0].compare("add_book")){

        addBook(Book(vCommandParts[1]));

    }

    printLibrary();

    return "blah";
}

void Library::printLibrary(){

    for( StoredBooks::iterator it = mLibrary.begin(); it != mLibrary.end(); ++it ) {
    	it->second.printBook();
    }

}

}
