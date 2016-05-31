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
#include <sstream>

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
			<< endl << "1 - Send Command" << endl << "Choose one option(0-1): ";

	cin >> opcao;

	switch (opcao) {
	case 0:
		exit(0);
		break;
	case 1:
		this->sendCommand();
		break;
	default:
		this->showMenu();
		break;
	}
}

void UI::sendCommand() {

	std::stringstream vCommand;
	string vPart;

	cout << "Enter Command" << endl;

    cin.ignore();

    while (std::getline(std::cin, vPart) && !vPart.empty()){
	    if( !vCommand.str().empty() ){
	        vCommand << '\007';
	    }
	    vCommand << vPart;
        std::cout << "" << vCommand.str() << std::endl;
	}
    
	_client.write("", "", vCommand.str());

	showMenu();
}

}
