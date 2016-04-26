/*
 * Menu.cpp
 *
 *  Created on: 24 Apr 2016
 *      Author: orobsonpires
 */

#include <UI.h>
#include <iostream>
#include <cstdlib>
#include <string>

namespace library {

UI::UI(Client& client) : _client(client){
}

UI::~UI() {
}

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

void UI::showMenu() {
	int opcao = 0;

	cout << "*********************************" << endl
			<< "* Welcome to library System *" << endl
			<< "*********************************" << endl << endl << "Select: "
			<< endl << "1 - Add book" << endl << "Choose one option(0-4): ";

	cin >> opcao;

	switch (opcao) {
	case 0:
		exit(0);
		break;
	case 1:
		this->addBook();
		break;
	default:
		this->showMenu();
		break;
	}
}

void UI::addBook() {

	string title;
	string user = "test";
	string action = "add_book";

	cout << endl << "*********************" << endl << "* Add book *" << endl
			<< "*********************" << endl << endl;

	cout << "Enter the title: ";

	cin >> title;

	cin.clear();
	cin.ignore();

	cout << endl;

	_client.write(user, action, title);

	showMenu();
}

}
