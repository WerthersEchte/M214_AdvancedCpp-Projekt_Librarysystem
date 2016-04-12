#include <string>

namespace library{

enum Status{Burrowed, Available, None};

class Book{

    static int IDCOUNTER;

    int mId;
    std::string mTitle;
    Status mBurrowed;

public:
    Book();
    Book( std::string aTitle );
    ~Book();

    std::string getTitle();
    int getId();

    bool isAvailable();
    bool burrow();
    bool bringBack();

    Status getStatus();

};

}
