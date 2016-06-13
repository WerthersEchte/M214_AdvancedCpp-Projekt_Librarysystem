#include "library.h"
#include <iostream>

namespace library{
	using std::cout;
	using std::endl;

	Library* Library::library = nullptr;

	Library::Library(){}

	Library::~Library(){}

	bool Library::addBook(Book _book){
		int id = _book.getId();
		cout << inventory.size() << endl;
		if( inventory.find(id) == inventory.end() ){
		    inventory[id] = _book;
			cout << "Add book with id: " << id << endl;
		    return true;
		}
		return false;
	}

	//Library::removeBook(int id){}

	//Library::updateBook(Book book){}



	Book Library::getBook(int _id){
		Book book = inventory.at(_id);	
		return book;
	}

	Library* Library::getLibrary(){
		if(library == nullptr){
			library= new Library();
		}
		return library;
	};

}

