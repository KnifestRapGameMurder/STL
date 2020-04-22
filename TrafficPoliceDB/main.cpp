#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<Windows.h>
#include<array>
#include<conio.h>
#include<boost/algorithm/string.hpp>


#define DEL std::cout<<"\n-------------------------------------------------------\n"

void printFullMap(const std::map<std::string, std::list<std::string>>& map);
void printOne(const std::map<std::string, std::list<std::string>>& map);

std::map<std::string, std::list<std::string>> init();
void insert(std::map<std::string, std::list<std::string>>& map);

void save(const std::map<std::string, std::list<std::string>>& map);
void load(std::map<std::string, std::list<std::string>>& map);

void menu();
void printMenu(std::array<bool, 5> optionActive);


//#define CHECKER

void main()
{
	setlocale(LC_ALL, "");

#ifdef CHECKER
	std::map<std::string, std::list<std::string>> PoliceDB;// = init();
	load(PoliceDB);
	printFullMap(PoliceDB);
#endif // CHECKER

	menu();
}



void menu()
{
	std::map<std::string, std::list<std::string>> PoliceDB = init();
	std::array<bool, 5> optionActive = { true,false,false,false,false };
	char key = 72;
	while (key != 27) {
		system("cls");
		printMenu(optionActive);
		key = _getch();
		for (int i = 0; i < optionActive.size(); i++)
		{
			if ( (key==72||key==80) && optionActive[i]) {
				optionActive[i] = false;
				if (key == 72) { i == 0 ? optionActive[optionActive.size() - 1] = true : optionActive[i - 1] = true; }
				else if (key == 80) { (i == optionActive.size() - 1) ? optionActive[0] = true : optionActive[i + 1] = true; }
				i = optionActive.size();
			}
			if (key == 13) {
				system("cls");
				do{
					if (optionActive[0])	load(PoliceDB);
					if (optionActive[1])	save(PoliceDB);
					if (optionActive[2])	insert(PoliceDB);
					if (optionActive[3])	printFullMap(PoliceDB);
					if (optionActive[4])	printOne(PoliceDB);
					key = _getch();		system("cls");
				} while (key != 27);
				key = 0;
			}
		}
	};
	
	
}

void printMenu(std::array<bool, 5> optionActive)
{
	std::cout << "\n\n";
	std::array<std::pair<std::string, std::string>,5> menuOptions = {
		std::pair<std::string,std::string>
		("\t\t>>>>>\tLOAD DB\t\t<<<<<\n","\t\t\tLOAD DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tSAVE DB\t\t<<<<<\n","\t\t\tSAVE DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tADD NEW\t\t<<<<<\n","\t\t\tADD NEW\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tPRINT FULL DB\t<<<<<\n","\t\t\tPRINT FULL DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tPRINT ONE\t<<<<<\n","\t\t\tPRINT ONE\n")
	};
	std::cout << "\n\t\t~~~ Traffic Police Database ~~~\n\n";
	for (int i = 0;i<menuOptions.size();i++)
	{
		if (optionActive[i]) {
			std::cout << menuOptions[i].first;
		}
		else
		{
			std::cout << menuOptions[i].second;
		}
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Enter] Choose\n";
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

void printOne(const std::map<std::string, std::list<std::string>>& map)
{
	std::cout << "Введите номер транспортного средства: ";
	std::string license_plate; 
	SetConsoleCP(1251);		std::getline(std::cin, license_plate);		SetConsoleCP(866);
	std::cout << "\n\n";
	for (std::pair<std::string, std::list<std::string>> m_it : map)
	{
		if (m_it.first == license_plate) {
			std::cout << m_it.first << " :\n";
			for (std::string l_it : m_it.second)
			{
				std::cout << "\t" << l_it<<"\n";
			}
		}
		else {
			std::cout << "Такого номера нету в базе";
			break;
		}
	}

}

void save(const std::map<std::string, std::list<std::string>>& map)
{
	std::ofstream fout("base.txt");
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
	system("start notepad base.txt");
}

std::map<std::string, std::list<std::string>> init()
{
	std::map<std::string, std::list<std::string>> PoliceDB =
	{
		std::pair<std::string,std::list<std::string>>
		("BI 0000 BI",{"превышение скорости","вождение в нетрезвом состоянии"}),

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
	std::string licensePlate;
	std::string violation;
	std::list<std::string> violationList;

	std::ifstream fin("base.txt");

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::getline(fin, licensePlate,':');
			std::cout << licensePlate << " : ";
			std::getline(fin, violation, ';');
			//std::cout << licensePlate << "\t" << violation << std::endl;
			boost::algorithm::split(violationList, violation, boost::is_any_of(","));
			//for (auto x : violationList)	std::cout << x<<"\t";	std::cout << std::endl;
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