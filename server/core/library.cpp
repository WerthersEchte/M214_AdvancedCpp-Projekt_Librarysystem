#include "library.h"

#include <map>
#include <stdexcept>

namespace library{

Library Library::LIBRARY;

Library::Library() :
mLibrary()
{};

Library Library::getLibrary()
{
    return LIBRARY;
};

bool Library::addBook( Book aBook )
{
    if( mLibrary.find( aBook.getId() ) == mLibrary.end() )
    {
        mLibrary[aBook.getId()] = aBook;
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

}
