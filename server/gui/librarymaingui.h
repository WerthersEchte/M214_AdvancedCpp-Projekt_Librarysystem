#ifndef _LibraryMainGUI_
#define _LibraryMainGUI_

#include "ui_librarymaingui.h"
#include "core/networkmanagement.h"

#include <QWidget>
#include <QMainWindow>
#include <QString>

namespace library{

class MainGUI: public QMainWindow, private Ui::LibraryMainGUI
{
    Q_OBJECT

    library::NetworkManagement* mServer;


public:
    MainGUI( QWidget *vParent = 0 );

public slots:
    void messageNetwork( QString aId, QString aMessage );

private slots:
    void addBook( bool vChecked );
    void editBook( bool vChecked );
    void selectBook(const QModelIndex &vIndex);

    void networkStartStop( bool vChecked );

};

}

#endif // _LibraryMainGUI_
