#ifndef LIBRARY_BOOK_HEADER
#define LIBRARY_BOOK_HEADER

#include <string>

namespace library{
	using std::string;


	class Book{
		int id;
		string name;
		bool borrowState;

	public:
		Book();
		Book(int _id, string _name);
		~Book();


		int getId();
		string getName();
		string setName(string name);
		bool isBorrowed();
		void setBorrowState(bool state);
		string toString();
	};

}

#endif