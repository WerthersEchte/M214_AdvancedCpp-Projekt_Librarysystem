#ifndef _LibraryViewModel_
#define _LibraryViewModel_

#include <QAbstractListModel>

namespace library{

class LibraryViewModel: public QAbstractListModel
{

    Q_OBJECT

public:

    explicit LibraryViewModel(QObject *vParent);

    int rowCount(const QModelIndex &vParent = QModelIndex()) const ;
    QVariant data(const QModelIndex &vIndex, int vRole = Qt::DisplayRole) const;

public slots:
    void changed( int vIndex );

};

}

#endif // _LibraryViewModel_
