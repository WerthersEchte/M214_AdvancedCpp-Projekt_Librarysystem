#include <string>

namespace library{
	using std::string;


	class Book{
		int id;
		string name;
		bool borrowState;

	public:
		Book();
		Book(string name);
		~Book();


		int getId();
		string getName();
		string setName(string name);
		bool isBorrowed();
		void setBorrowState(bool state);
	};

}
