#include <string>

namespace library{

class Book{

    static int IDCOUNTER;

    int mId;
    std::string mName;
    bool mBurrowed;

public:
    Book();
    Book( std::string aName );
    ~Book();

    std::string getName();
    int getId();

    bool isAvailable();
    bool burrow();
    bool bringBack();

};

}
