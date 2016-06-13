#include <iostream>
#include "core/networkmanagement.h"


int main(int argc, char* argv[]) {
	library::NetworkManagement server(8000);
	server.run();
	char userInput[128];
	std::cin.getline(userInput, 128);
	server.stop();
	return 0;
}