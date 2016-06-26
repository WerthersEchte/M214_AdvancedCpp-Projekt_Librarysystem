#ifndef _LibraryUser_
#define _LibraryUser_

#include "definitions.h"

#include <string>
#include <vector>

#include <QObject>
#include <QString>

namespace library{

class User: public QObject{

    Q_OBJECT

    static int IDCOUNTER;

    int mId;
    std::string mUserName, mPassword;
    std::vector<Permission> mPermissions;
    std::vector<int> mBorrowedBooks;

public:
    User();
    User( const std::string& mUserName, const std::string& mPassword, const std::vector<Permission>& aPermissions );
    User( const User& aUser );
    ~User();

    int getId() const;
    std::string getUserName() const;
    void editUserName( const std::string& aUserName );
    std::string getPassword() const;
    void editPassword( const std::string& aPassword );

    bool hasPermission( Permission aPermission ) const;
    void addPermission( Permission aPermission );
    void removePermission( Permission aPermission );

    std::vector<int> getBorrowedBooks() const;
    bool addBorrowedBook( int aBookId );
    bool removeBorrowedBook( int aBookId );

    std::string printUser( bool aEndLine = true ) const;

signals:
    void changed( const QString& vUserName );
};

}

#endif // _LibraryUser_
