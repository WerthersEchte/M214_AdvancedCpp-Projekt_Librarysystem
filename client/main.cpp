#include "gui/librarymaingui.h"

#include <QApplication>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);
    library::MainGUI vMainGUI;
    vMainGUI.show();
    return app.exec();
/*
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);

    auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});

    tcp::socket s(io_service);

    library::Client c(io_service, endpoint_iterator, s);

    library::UI ui(c);

    ui.showMenu();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;*/
}
