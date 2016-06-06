#include "library.h"
#include <iostream>

namespace library{
	using std::cout;
	using std::endl;


	Library::Library(){}

	Library::~Library(){}

	bool Library::addBook(Book _book){
		int id = _book.getId();

		if( inventory.find(id) == inventory.end() ){
		    inventory[id] = _book;
			std::cout << inventory.size() << std::endl;
			cout << "Add book with id: " << id << endl;
		    return true;
		}
		return false;
	}

	//Library::removeBook(int id){}

	//Library::updateBook(Book book){}



	Book Library::getBook(int _id){
		std::cout << inventory.size() << std::endl;
		Book book = inventory.at(_id);	
		return book;
	}
}

