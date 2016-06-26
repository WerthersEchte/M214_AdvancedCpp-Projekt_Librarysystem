#ifndef _UserViewModel_
#define _UserViewModel_

#include <QAbstractListModel>
#include <QString>

namespace library{

class UserViewModel: public QAbstractListModel
{

    Q_OBJECT

public:

    explicit UserViewModel(QObject *vParent);

    int rowCount(const QModelIndex &aParent = QModelIndex()) const ;
    QVariant data(const QModelIndex &aIndex, int aRole = Qt::DisplayRole) const;

public slots:
    void changed( const QString& aUserName );
    void userAdded( const QString& aUserName );

};

}

#endif // _LibraryViewModel_
