#ifndef _LibraryMainGUI_
#define _LibraryMainGUI_

#include "ui_mainwindow.h"
#include "core/Client.h"

#include <QWidget>
#include <QMainWindow>
#include <QString>

namespace library{

class MainGUI: public QMainWindow, private Ui::ClientMainGUI
{
    Q_OBJECT

    Client* mClient;

public:
    MainGUI( QWidget *vParent = 0 );

private slots:
    void connectToServer(bool);
    void sendData(bool);
    
public slots:
    void getData(QString aData);

};

}

#endif // _LibraryMainGUI_
