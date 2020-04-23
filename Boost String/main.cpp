#include<iostream>
#include<boost/algorithm/string.hpp>

#define PRINT1 std::cout << str1 << std::endl
#define PRINT2 std::cout << str2 << std::endl

//#define FIRST_EXAMPLE
//#define C_WIDE_STRINGS
void main()
{
#ifdef FIRST_EXAMPLE
	std::string str1(" hello world");
	boost::to_upper(str1);
	PRINT1;

	boost::trim(str1);
	PRINT1;

	std::string str2 = boost::to_lower_copy(
		boost::ireplace_first_copy(
			str1, "hello", "goodbye"
		)
	);
	PRINT2;
#endif // DEBUG

#ifdef C_WIDE_STRINGS
	using namespace std;
	setlocale(LC_ALL, ".OCP");
	wchar_t str[256] = L"Привет ";
	wcout << str;
	wcin.getline(str, 256);
	wcout << str << std::endl;
	wcout << wcslen(str) << std::endl;
	std::
#endif // C_WIDE_STRINGS

		using namespace

	
}