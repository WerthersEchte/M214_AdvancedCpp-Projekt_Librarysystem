#ifndef _LibraryDefinitions_
#define _LibraryDefinitions_

#include <string>

namespace library{

    namespace command{
        // root-commands
        const std::string LOGIN = "login";
        const std::string LOGOUT = "logout";
        const std::string BOOK = "book";
        const std::string USER = "user";

        // book-subcommands
        namespace book{
            const std::string ADD = "add";
            const std::string EDIT = "edit";
            const std::string SEARCH = "search";
            const std::string GET = "get";
            const std::string BURROW = "burrow";
            const std::string RETURN = "return";
        }
        // user-subcommands
        namespace user{
            const std::string ADD = "add";
            const std::string CHANGEPASSWORD = "changepassword";
            const std::string GET = "get";
            const std::string BURROWEDBOOKS = "burrowedbooks";
        }
    }
    enum Status{Burrowed, Available, None};

    enum class Splitter: char{ TYPE=':', COMMAND=';'};
    enum class Permission{Users, Books};

}

#endif // _LibraryDefinitions_
