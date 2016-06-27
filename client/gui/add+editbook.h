#ifndef _LibraryAddEditBook_
#define _LibraryAddEditBook_

#include "ui_add+editbook.h"

#include <QWidget>
#include <QDialog>

namespace library{

class AddEditBook: public QDialog, public Ui::AddEditBook {
    Q_OBJECT

public:
    AddEditBook(QWidget *parent = 0);

};

}

#endif // _LibraryAddEditBook_

