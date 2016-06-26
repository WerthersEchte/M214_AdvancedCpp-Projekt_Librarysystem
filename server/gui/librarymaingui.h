#ifndef _LibraryMainGUI_
#define _LibraryMainGUI_

#include "ui_librarymaingui.h"
#include "core/networkmanagement.h"
#include "core/user.h"

#include <map>

#include <QWidget>
#include <QMainWindow>
#include <QString>
#include <QCheckBox>

namespace library{

class MainGUI: public QMainWindow, private Ui::LibraryMainGUI
{
    Q_OBJECT

    library::NetworkManagement* mServer;

    std::map<library::Permission, QCheckBox*> mPermissions;

public:
    MainGUI( QWidget *vParent = 0 );

public slots:
    void messageNetwork( const QString& aId, const QString& aMessage );

private slots:
    void addBook( bool vChecked );
    void editBook( bool vChecked );
    void selectBook(const QModelIndex &vIndex);

    void selectUser(const QModelIndex &vIndex);
    void changedPermissions(int aState);

    void networkStartStop( bool vChecked );

    void on_actionLoad_books_triggered();

private:
    void loadBooks( const std::string& aFileWithBooks );

};

}

#endif // _LibraryMainGUI_
