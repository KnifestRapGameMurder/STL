#include<iostream>
#include<array>
#include<vector>
#include<deque>
#include<forward_list>


/*
-----------------------------------------------------------------------------------
STL - Standard Template Library.
Container - ýòî îáúåêò, êîòîðûé îðãàíèçóåò õðàíåíèå äðóãèõ îáúåêòîâ â ïàìÿòè.
1. Sequence containers:
	array;
	vector;
	deque;
	forward_list;
	list;
2. Associative containers:
	map;
	multimap;
	set;
	multiset;
3. Container adaptors:
	stack;
	queue - î÷åðåäü;
	priority_queue - î÷åðåäü ñ ïðèîðèòåòàìè;
-----------------------------------------------------------------------------------
*/

//#define ARRAY
//#define VECTOR
//#define DEQUE
//#define FORWARD_LIST

const int SIZE = 5;

#ifdef ARRAY
void print(const std::array<int, SIZE>& arr)
{
	for (std::array<int, SIZE>::const_iterator it = arr.begin(); it != arr.end(); it++)
	{
		//(*it)++;
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
}
#endif // ARRAY


void main()
{

#ifdef ARRAY
	//array - ýòî êîíòåéíåð, êîòîðûé õðàíèò îáúåêòû â ñòàòè÷åñêîì ìàññèâå.
	std::array<int, SIZE> arr = { 3, 5, 8 };
	try
	{
		for (int i = 0; i < SIZE * 2; i++)
		{
			std::cout << arr.at(i) << "\t";
		}
		std::cout << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	for (std::array<int, SIZE>::iterator it = arr.begin(); it != arr.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;

	for (std::array<int, SIZE>::reverse_iterator rit = arr.rbegin(); rit != arr.rend(); rit++)
	{
		std::cout << *rit << "\t";
	}
	std::cout << std::endl;

	print(arr);
#endif // ARRAY

#ifdef VECTOR
	//vector - ýòî êîíòåéíåð, êîòîðûé õðàíèò äàííûå â âèäå äèíàìè÷åñêîãî ìàññèâà.
	std::vector<int> vec{ 0,1,1,2,3,5,8,13,21,34 };
	vec.push_back(55);
	try
	{
		for (int i = 0; i < vec.size(); i++)
		{
			//std::cout << vec[i] << "\t";
			std::cout << vec.at(i) << "\t";
		}
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "vector size:\t" << vec.size() << std::endl;
	vec.shrink_to_fit();
	std::cout << "vector capacity:" << vec.capacity() << std::endl;
	std::cout << "vector max size:" << vec.max_size() << std::endl;

	int index;
	int value;
	std::cout << "Type index: "; std::cin >> index;
	std::cout << "Type value: "; std::cin >> value;
	//std::vector<int>::iterator position = vec.begin() + index;
	//vec.insert(position, value);
	vec.insert(vec.begin() + index, 3, value);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	std::cout << "vector size:\t" << vec.size() << std::endl;
	std::cout << "vector capacity:" << vec.capacity() << std::endl;
	std::cout << "vector max size:" << vec.max_size() << std::endl;
#endif

#ifdef DEQUE
	std::deque<int> de{ 3,5,8,13 };
	de.push_front(0);
	de.push_front(1);
	de.push_front(1);
	de.push_front(2);
	for (int i : de)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
#endif // DEQUE

#ifdef FORWARD_LIST
	std::forward_list<int> list = { 3,5,8,13,21 };
	/*for (int i = 0; i < 5; i++)
	{
		//NO SUBSCRIPT OPERATOR!!!
		std::cout << list[i] << "\t";
	}*/
	for (std::forward_list<int>::iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	int index;
	int value;
	std::cout << "Type index: "; std::cin >> index;
	std::cout << "Type value: "; std::cin >> value;

	list.insert_after(, value);
#endif // FORWARD_LIST

	
	
}