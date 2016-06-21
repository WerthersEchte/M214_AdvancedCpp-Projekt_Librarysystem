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

};

Library* Library::getLibrary()
{
    if(LIBRARY == nullptr){
        LIBRARY = new Library();
    }
    return LIBRARY;
};

int Library::addBook( const Book& aBook )
{
    if( mLibrary.find( aBook.getId() ) == mLibrary.end() )
    {
        mLibrary[aBook.getId()] = aBook;
        emit changed(aBook.getId());
        return aBook.getId();
    }
    return 0;
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
    /*
    for( StoredBooks::iterator it = mLibrary.begin(); it != mLibrary.end(); ++it ) {
    	vBooks.push_back( it->second );
    }

    if( !aTitle.empty() ){
        vBooks = searchTitle( aTitle, vBooks );
    }

    if( aBurrowed != Status::None ){
        vBooks = searchBurrowed( aBurrowed, vBooks );
    }
    */
    return vBooks;
};

std::vector<Book> Library::searchTitle( std::string aTitle, const std::vector<Book>& aBooks )
{
    std::vector<Book> vFoundBooks;
    /*
    for( Book vBook : aBooks ){
        if( vBook.getTitle().find( aTitle ) != std::string::npos ){
            vFoundBooks.push_back( vBook );
        }
    }
    */
    return vFoundBooks;
};

std::vector<Book> Library::searchBurrowed( Status aBurrowed, const std::vector<Book>& aBooks )
{
    std::vector<Book> vFoundBooks;
    /*
    for( Book vBook : aBooks ){
        if( vBook.getStatus() == aBurrowed ){
            vFoundBooks.push_back( vBook );
        }
    }
    */
    return vFoundBooks;
};

std::string Library::parseCommand( const std::string& aCommand ){

    std::vector< std::string > vCommandParts;

    boost::split( vCommandParts,
                  aCommand,
                  [](char aCharacter) { return aCharacter == '|'; } );

    if(!vCommandParts[0].compare("add")){

        addBook(Book(vCommandParts[1]));

    }

    return "blah";
}

void Library::printLibrary(){

    for( StoredBooks::iterator it = mLibrary.begin(); it != mLibrary.end(); ++it ) {
    	it->second.printBook();
    }

}

}
