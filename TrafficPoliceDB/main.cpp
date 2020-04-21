#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<Windows.h>


#define DEL std::cout<<"\n-------------------------------------------------------\n"
void printFullMap(const std::map<std::string, std::list<std::string>>& map);
void save(const std::map<std::string, std::list<std::string>>& map);
std::map<std::string, std::list<std::string>> init();
void load(std::map<std::string, std::list<std::string>>& map);
void insert(std::map<std::string, std::list<std::string>>& map);



void main()
{
	setlocale(LC_ALL, "");
	
	std::map<std::string, std::list<std::string>> PoliceDB = init();

	printFullMap(PoliceDB);
	//save(PoliceDB);
	insert(PoliceDB);
	printFullMap(PoliceDB);
}

void printFullMap(const std::map<std::string, std::list<std::string>>& map)
{
	/*for (std::map<std::string, std::list<std::string>>::iterator m_it = map.begin(); m_it != map.end(); m_it++)
	{
		std::cout << m_it->first<<" :\n";
		for (auto l_it : m_it->second)
		{
			std::cout << l_it << "\t";
		}
		DEL;
	}*/
	for (std::pair<std::string, std::list<std::string>> m_it : map)
	{
		std::cout << m_it.first << " :\n";
		for (std::string l_it : m_it.second)
		{
			std::cout << l_it << "\t";
		}
		DEL;
	}
}
void save(const std::map<std::string, std::list<std::string>>& map)
{
	std::ofstream fout("TrafficPoliceDB.txt");
	for (std::pair<std::string, std::list<std::string>> m_it : map)
	{
		fout << m_it.first << " : ";
		for (std::string l_it : m_it.second)
		{
			fout << l_it << ",";
		}
		fout.seekp(-1, std::ios::cur);
		fout << ";\n";

	}
	fout.close();
	system("start notepad TrafficPoliceDB.txt");
}

std::map<std::string, std::list<std::string>> init()
{
	std::map<std::string, std::list<std::string>> PoliceDB =
	{
		std::pair<std::string,std::list<std::string>>
		("BI 0000 BI",{"привышение скорости","вождение в нетрезвом состоянии"}),

		std::pair<std::string,std::list<std::string>>
		("BI 0001 BI",{"езда по встречке"}),

		std::pair<std::string,std::list<std::string>>
		("BI 0002 BI",{"парковка в неположеном месте"}),

		std::pair<std::string,std::list<std::string>>
		("BI 0003 BI",{"проезд на красный","плюнул в полицейского"})
	};
	return PoliceDB;
}

void load(std::map<std::string, std::list<std::string>>& map)
{
	map.clear();
	std::string license_plate;
	std::list<std::string> violation;

	std::ifstream fin("TrafficPoliceDB.txt");

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::getline(fin, license_plate,':');

		}
	}
	else {
		std::cerr << "Error: file id not found";
	}
}

void insert(std::map<std::string, std::list<std::string>>& map)
{
	std::string license_plate;
	std::string violation;

	std::cout << "Введите номер автомобиля: ";
	SetConsoleCP(1251);		std::getline(std::cin,license_plate);		SetConsoleCP(866);

	std::cout << "Введите правонарушение: ";
	SetConsoleCP(1251);		std::getline(std::cin, violation);			SetConsoleCP(866);

	std::map<std::string, std::list<std::string>>::iterator offender =  map.find(license_plate);

	if (offender != map.end())
	{
		offender->second.push_back(violation);
	}
	else
	{
		map.insert(std::pair<std::string, std::list<std::string>>(license_plate, { violation }));
	}
}