#ifndef LIBRARY_LIBRARY_HEADER
#define LIBRARY_LIBRARY_HEADER

#include "book.h"
#include <map>


namespace library{
	using std::map;
	using std::string;

	class Library{
	private:
		map<int, Book> inventory;


	public:
 		Library();
		~Library();

		bool addBook(Book book);
		bool removeBook(int id);
		bool updateBook(Book book);
		Book getBook(int id);
	};
}

#endif