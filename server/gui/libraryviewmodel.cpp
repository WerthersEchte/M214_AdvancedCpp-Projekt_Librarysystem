#include "libraryviewmodel.h"

#include "core/library.h"

#include <iostream>

namespace library{



LibraryViewModel::LibraryViewModel(QObject *vParent):
    QAbstractListModel(vParent)
{
    connect(Library::getLibrary(), SIGNAL(changed(int)), this, SLOT(changed(int)));
};

int LibraryViewModel::rowCount(const QModelIndex &vParent ) const
{
    return Library::getLibrary()->getNumberOfBooks();
};

QVariant LibraryViewModel::data(const QModelIndex &vIndex, int vRole ) const
{
    if( Library::getLibrary()->getBook( vIndex.row() ) == nullptr ){
        return QVariant();
    }

    if (vRole == Qt::DisplayRole)
    {
       return QString("%1-\"%2\"").arg( Library::getLibrary()->getBook( vIndex.row() )->getId() ).arg( QString::fromUtf8( Library::getLibrary()->getBook( vIndex.row() )->getTitle().c_str()) );
    }
    return QVariant();
};

void LibraryViewModel::changed( int vIndex ){
    QModelIndex vPosition = createIndex(vIndex,0);
    emit dataChanged(vPosition, vPosition);
}

};
