#include "core/networkmanagement.h"
#include "gui/librarymaingui.h"

#include <QApplication>

#include <iostream>

#include "core/library.h"
#include "core/book.h"

int main(int argc, char* argv[]) {

	/*QApplication app(argc, argv);
    library::MainGUI vMainGUI;
    vMainGUI.show();
    return app.exec();*/

    library::NetworkManagement server;
    server.start();
    char userInput[128];
    std::cin.getline(userInput, 128);

    return 0;

}
