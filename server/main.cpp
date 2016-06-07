#include "gui/librarymaingui.h"

#include <QApplication>

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
    library::MainGUI vMainGUI;
    vMainGUI.show();
    return app.exec();

}
