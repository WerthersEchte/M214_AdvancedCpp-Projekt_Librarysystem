#include "library.h"

#include <map>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "definitions.h"
#include "core/usermanagement.h"
#include "core/user.h"

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

int Library::getNumberOfBooks() const
{
    return mLibrary.size();
};

std::string Library::parseCommand( const std::string& aUser, const std::string& aCommand ){

    std::vector< std::string > vCommandParts;

    boost::split( vCommandParts,
                  aCommand,
                  [](char aCharacter) { return aCharacter == static_cast<char>(Splitter::COMMAND); } );

    if( vCommandParts.size() > 1 ){
        if( UserManagement::getUserManagement()->getUser(aUser)->hasPermission(Permission::Books) && !vCommandParts[0].compare(command::book::ADD) ){

            if( addBook(Book(vCommandParts[1], vCommandParts.size() >= 3?vCommandParts[2]:"", vCommandParts.size() >= 4?vCommandParts[3]:"", vCommandParts.size() >= 5?vCommandParts[4]:"", vCommandParts.size() >= 6?vCommandParts[5]:"")) ){
                return std::string("added book to library");
            } else {
                return std::string("can not add book to library");
            }

        } else if( UserManagement::getUserManagement()->getUser(aUser)->hasPermission(Permission::Books) && !vCommandParts[0].compare(command::book::EDIT) ){

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

        } else if( !vCommandParts[0].compare(command::book::SEARCH) ){

            std::vector<int> vBookIds;

            for( StoredBooks::iterator it = mLibrary.begin(); it != mLibrary.end(); ++it ) {
                for( int vI = 1; vI < vCommandParts.size(); ++vI ){
                    if( it->second.getTitle().find( vCommandParts[vI] ) != std::string::npos ||
                        it->second.getAuthor().find( vCommandParts[vI] ) != std::string::npos ||
                        it->second.getPublisher().find( vCommandParts[vI] ) != std::string::npos ||
                        it->second.getISBN().find( vCommandParts[vI] ) != std::string::npos ||
                        it->second.getDatePublished().find( vCommandParts[vI] ) != std::string::npos ){

                        vBookIds.push_back( it->second.getId() );
                        break;
                    }
                }
            }

            std::stringstream vBooks;

            for( int vBookId : vBookIds ){
                if( getBook(vBookId) != nullptr ){
                    vBooks << getBook(vBookId)->printBook();
                }
            }

            return vBooks.str();

        }  else if( !vCommandParts[0].compare(command::book::GET) ){

            std::stringstream vBooks;

            for( int vI = 1; vI < vCommandParts.size(); ++vI ){
                if( getBook(stoi(vCommandParts[vI])) != nullptr ){
                    vBooks << getBook(stoi(vCommandParts[vI]))->printBook();
                } else {
                    vBooks << "unknown bookid: " << vCommandParts[vI] << "\n";
                }
            }

            return vBooks.str();

        } else if( !vCommandParts[0].compare(command::book::BURROW) ){

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

        } else if( !vCommandParts[0].compare(command::book::RETURN) ){

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

void Library::printLibrary() const{

    for( StoredBooks::const_iterator it = mLibrary.begin(); it != mLibrary.end(); ++it ) {
    	it->second.printBook();
    }

}

}
