#include<iostream>
#include<string>
#include<list>
#include<map>

#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		std::pair<int,std::string>(0,"Sunday"),
		std::pair<int,std::string>(1,"Monday"),
		std::pair<int,std::string>(2,"Tuesday"),
		std::pair<int,std::string>(3,"Wednesday"),
		std::pair<int,std::string>(4,"Thursday"),
		std::pair<int,std::string>(5,"Friday"),
		std::pair<int,std::string>(6,"Saturday")
	};

	/*int number;
	std::cout << "¬ведите ваше любимое число от 1 до 7: ";
	std::cin >> number;
	std::cout << "¬аш любимый день недели: " << week.find(number % 7)->second << std::endl;*/

	for (std::pair<int, std::string> day : week)
	{
		std::cout << day.first << "\t" << day.second << std::endl;
	}

	/*for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); it++)
	{
		std::cout << it->first << "\t" << it->second << std::endl;
	}*/
#endif // STL_MAP

	

}