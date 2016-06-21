#ifndef _LibraryUser_
#define _LibraryUser_

#include <string>
#include <vector>

#include <QObject>
#include <QString>

namespace library{

enum class Permission{Users, Books};

class User: public QObject{

    Q_OBJECT

    static int IDCOUNTER;

    int mId;
    std::string mUserName, mPassword;
    std::vector<Permission> mPermissions;
    std::vector<int> mBorrowedBooks;

public:
    User();
    User( std::string mUserName, std::string mPassword, const std::vector<Permission>& aPermissions );
    User( const User& aUser );
    ~User();

    int getId();
    std::string getUserName();
    std::string getUserName() const;
    void editUserName( std::string aUserName );
    std::string getPassword();
    std::string getPassword() const;
    void editPassword( std::string aPassword );

    bool hasPermission( Permission aPermission );
    void addPermission( Permission aPermission );
    void removePermission( Permission aPermission );

    std::vector<int> getBorrowedBooks();
    bool addBorrowedBook( int aBookId );
    bool removeBorrowedBook( int aBookId );

    std::string printUser( bool aEndLine = true );

signals:
    void changed( QString vUserName );
};

}

#endif // _LibraryUser_
