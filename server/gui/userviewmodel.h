#ifndef _UserViewModel_
#define _UserViewModel_

#include <QAbstractListModel>
#include <QString>

namespace library{

class UserViewModel: public QAbstractListModel
{

    Q_OBJECT

public:

    UserViewModel(QObject *vParent);

    int rowCount(const QModelIndex &aParent = QModelIndex()) const ;
    QVariant data(const QModelIndex &aIndex, int aRole = Qt::DisplayRole) const;

public slots:
    void changed( QString aUserName );
    void userAdded( QString aUserName );

};

}

#endif // _LibraryViewModel_
