#include "userviewmodel.h"

#include "core/usermanagement.h"

#include <iostream>

namespace library{

UserViewModel::UserViewModel(QObject *aParent):
    QAbstractListModel(aParent)
{
    connect(library::UserManagement::getUserManagement(), SIGNAL(userAdded(QString)), this, SLOT(userAdded(QString)));
};

int UserViewModel::rowCount(const QModelIndex &aParent ) const
{
    return UserManagement::getUserManagement()->getNumberOfUsers();
};

QVariant UserViewModel::data(const QModelIndex &aIndex, int aRole ) const
{
    if( UserManagement::getUserManagement()->getUser( aIndex.row() ) == nullptr ){
        return QVariant();
    }

    if (aRole == Qt::DisplayRole)
    {
       return QString( UserManagement::getUserManagement()->getUser( aIndex.row() )->getUserName().c_str() );
    }
    return QVariant();
};

void UserViewModel::changed( QString aUserName ){
    QModelIndex vPosition = createIndex(UserManagement::getUserManagement()->getUser( aUserName.toStdString() )->getId(),0);
    emit dataChanged(vPosition, vPosition);
}

void UserViewModel::userAdded( QString aUserName ){
    connect(UserManagement::getUserManagement()->getUser( aUserName.toStdString() ), SIGNAL(changed(QString)), this, SLOT(changed(QString)));
    changed(aUserName);
}

};
