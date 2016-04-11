#include <iostream>
#include "core/library.h"


using namespace library;
using library::Book;
using library::Library;


int main(int argc, char *argv[]){

	Book book = Book("testBook");
	Library library = Library();

	library.addBook(book);
	library.addBook(book);
	
	Book book2 = library.getBook(4);
	std::cout << "Get book with name: " << book2.getName() << std::endl;

}
