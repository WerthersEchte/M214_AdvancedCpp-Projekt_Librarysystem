#include <iostream>
#include "core/library.h"
#include "core/networkmanagement.h"
#include <memory>

int main(int argc, char* argv[]) {
	std::shared_ptr<library::Library> library = std::make_shared<library::Library>();
	library::NetworkManagement server(library);
	server.run();
	char userInput[128];
	std::cin.getline(userInput, 128);
	return 0;
}