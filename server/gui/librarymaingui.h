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
    MainGUI( QWidget *vParent = 0 );

public slots:
    //void libraryChanged( int vId );

private slots:
    void addBook( bool vChecked );
    void editBook( bool vChecked );
    void selectBook(const QModelIndex &vIndex);

};

}

#endif // _LibraryMainGUI_
