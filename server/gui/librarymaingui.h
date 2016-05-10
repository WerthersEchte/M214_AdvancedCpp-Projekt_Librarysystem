#ifndef _LibraryMainGUI_
#define _LibraryMainGUI_

#include "ui_librarymaingui.h"

#include <QWidget>
#include <QMainWindow>

namespace library{

class MainGUI: public QMainWindow, private Ui::LibraryMainGUI
{
    Q_OBJECT

public:
    MainGUI(QWidget *parent = 0);

};

}

#endif // _LibraryMainGUI_
