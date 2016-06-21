#include "library.h"

#include <map>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "core/usermanagement.h"
#include "core/user.h"
#include "core/networkconnection.h"

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

bool Library::addBook( const Book& aBook )
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

std::string Library::parseCommand( const std::string& aUser, const std::string& aCommand ){

    std::vector< std::string > vCommandParts;

    boost::split( vCommandParts,
                  aCommand,
                  [](char aCharacter) { return aCharacter == static_cast<char>(Splitter::COMMAND); } );

    if( vCommandParts.size() > 1 ){
        if( UserManagement::getUserManagement()->getUser(aUser)->hasPermission(Permission::Books) && !vCommandParts[0].compare("add") ){

            if( addBook(Book(vCommandParts[1], vCommandParts.size() >= 3?vCommandParts[2]:"", vCommandParts.size() >= 4?vCommandParts[3]:"", vCommandParts.size() >= 5?vCommandParts[4]:"", vCommandParts.size() >= 6?vCommandParts[5]:"")) ){
                return std::string("added book to library");
            } else {
                return std::string("can not add book to library");
            }

        } else if( UserManagement::getUserManagement()->getUser(aUser)->hasPermission(Permission::Books) && !vCommandParts[0].compare("edit") ){

            if( getBook(stoi(vCommandParts[1])) != nullptr ){

                getBook(stoi(vCommandParts[1]))->editTitle( vCommandParts.size() >= 3?vCommandParts[2]:"" );
                getBook(stoi(vCommandParts[1]))->editAuthor( vCommandParts.size() >= 4?vCommandParts[3]:"" );
                getBook(stoi(vCommandParts[1]))->editPublisher( vCommandParts.size() >= 5?vCommandParts[4]:"" );
                getBook(stoi(vCommandParts[1]))->editISBN( vCommandParts.size() >= 6?vCommandParts[5]:"" );
                getBook(stoi(vCommandParts[1]))->editDatePublished(  vCommandParts.size() >= 7?vCommandParts[6]:"" );

                return std::string("edited book");
            } else {
                return std::string("unknown book to edit");
            }

        } else if( !vCommandParts[0].compare("get") ){

            std::stringstream vBooks;

            for( int vI = 1; vI < vCommandParts.size(); ++vI ){
                if( getBook(stoi(vCommandParts[vI])) != nullptr ){
                    vBooks << getBook(stoi(vCommandParts[vI]))->printBook();
                } else {
                    vBooks << "unknown bookid: " << vCommandParts[vI] << "\n";
                }
            }

            return vBooks.str();

        } else if( !vCommandParts[0].compare("borrow") ){

            std::stringstream vBooks;

            for( int vI = 1; vI < vCommandParts.size(); ++vI ){

                if( getBook(stoi(vCommandParts[vI])) != nullptr ){

                    if( getBook(stoi(vCommandParts[vI]))->burrow() && UserManagement::getUserManagement()->getUser(aUser)->addBorrowedBook( stoi( vCommandParts[vI] ) ) ){
                        vBooks << "borrowed book: " << vCommandParts[vI] << "\n";
                    } else {
                        vBooks << "can not borrow book: " << vCommandParts[vI] << "\n";
                    }

                } else {
                    vBooks << "unknown bookid: " << vCommandParts[vI] << "\n";
                }

            }

            return vBooks.str();

        } else if( !vCommandParts[0].compare("return") ){

            std::stringstream vBooks;

            for( int vI = 1; vI < vCommandParts.size(); ++vI ){

                if( getBook(stoi(vCommandParts[vI])) != nullptr ){

                    if( getBook(stoi(vCommandParts[vI]))->bringBack() && UserManagement::getUserManagement()->getUser(aUser)->removeBorrowedBook( stoi(vCommandParts[vI] ) ) ){
                        vBooks << "returned book: " << vCommandParts[vI] << "\n";
                    } else {
                        vBooks << "can not return book: " << vCommandParts[vI] << "\n";
                    }

                } else {
                    vBooks << "unknown bookid: " << vCommandParts[vI] << "\n";
                }
            }

            return vBooks.str();
        }

    }

    return std::string("unknown command");

}

void Library::printLibrary(){

    for( StoredBooks::iterator it = mLibrary.begin(); it != mLibrary.end(); ++it ) {
    	it->second.printBook();
    }

}

}
