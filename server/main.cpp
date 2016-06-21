#include "gui/librarymaingui.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    library::MainGUI vMainGUI;
    vMainGUI.show();
    return app.exec();

}
