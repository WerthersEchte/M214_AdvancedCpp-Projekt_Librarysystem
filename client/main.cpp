#include "gui/librarymaingui.h"

//#include <QApplication>

//using boost::asio::ip::tcp;

//enum { max_length = 1024 };

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    library::MainGUI vMainGUI;
    vMainGUI.show();
    return app.exec();
}
