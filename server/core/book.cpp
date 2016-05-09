#include "book.h"
#include <iostream>

namespace library{
	using std::cout;
	using std::endl;
	using std::string;

	/***************************
	* Konstruktor
	****************************/
	Book::Book(){}

	Book::Book(std::string _name){
		id = 4;
		name = _name;
		cout << name << endl;
	}

	/***************************
	* Destruktor
	****************************/
	Book::~Book(){}

	/***************************
	* Getter
	****************************/
	int Book::getId(){
		return id;
	}

	string Book::getName(){
		return name;
	}
}



