#include <iostream>
#include "core/library.h"
#include "core/networkmanagement.h"

int main(int argc, char* argv[]) {
	library::Library* library = new library::Library();
	library::NetworkManagement server(library);
	server.run();
	char userInput[128];
	std::cin.getline(userInput, 128);
	return 0;
}