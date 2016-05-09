#include <iostream>
#include "core/library.h"
#include "core/networkmanagement.h"

int main(int argc, char* argv[]) {

	library::NetworkManagement server;
	server.start();
	char userInput[128];
	std::cin.getline(userInput, 128);

	return 0;

}