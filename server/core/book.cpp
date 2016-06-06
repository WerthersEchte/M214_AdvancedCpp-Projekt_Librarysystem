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

	Book::Book(int _id, std::string _name){
		id = _id;
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


	string Book::toString() {
		return std::to_string(id) + ";" + name;
	}


}



