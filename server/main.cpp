#include <iostream>
#include "core/library.h"
#include "core/networkmanagement.h"
#include <memory>

int main(int argc, char* argv[]) {
	std::shared_ptr<library::Library> library = std::make_shared<library::Library>();
	library::NetworkManagement server(library, 8000);
	server.run();
	char userInput[128];
	std::cin.getline(userInput, 128);
	server.stop();
	return 0;
}