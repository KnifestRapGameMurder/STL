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

#define LIC_PLATE_INP std::cout << "Введите номер транспортного средства: ";std::string licensePlate;SetConsoleCP(1251);		std::getline(std::cin, licensePlate);		SetConsoleCP(866);
#define VIO_INP std::cout << "Введите правонарушение: ";std::string violation;SetConsoleCP(1251);		std::getline(std::cin, violation);			SetConsoleCP(866);

void printFullMap(const std::map<std::string, std::list<std::string>>& map);
void printOne(const std::map<std::string, std::list<std::string>>& map);

std::map<std::string, std::list<std::string>> init();
void insert(std::map<std::string, std::list<std::string>>& map);

void removePair(std::map<std::string, std::list<std::string>>& map);
void removeViol(std::map<std::string, std::list<std::string>>& map);

void save(const std::map<std::string, std::list<std::string>>& map);
void load(std::map<std::string, std::list<std::string>>& map);

void menu();
void printMenu(std::array<bool, 7> optionActive);


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
	std::array<bool, 7> optionActive = { true,false,false,false,false,false,false };
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
					if (optionActive[5])	removePair(PoliceDB);
					if (optionActive[6])	removeViol(PoliceDB);
					key = _getch();		system("cls");
				} while (key != 27);
				key = 0;
			}
		}
	};
}

void printMenu(std::array<bool, 7> optionActive)
{
	std::cout << "\n\n";
	std::array<std::pair<std::string, std::string>,7> menuOptions = {
		std::pair<std::string,std::string>
		("\t\t>>>>>\tLOAD DB\t\t<<<<<\n","\t\t\tLOAD DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tSAVE DB\t\t<<<<<\n","\t\t\tSAVE DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tADD NEW\t\t<<<<<\n","\t\t\tADD NEW\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tPRINT FULL DB\t<<<<<\n","\t\t\tPRINT FULL DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tPRINT ONE\t<<<<<\n","\t\t\tPRINT ONE\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tERASE\t\t<<<<<\n","\t\t\tERASE\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tREMOVE VIOL\t<<<<<\n","\t\t\tREMOVE VIOL\n")
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
	/*for (std::map<std::string, std::list<std::string>>::const_iterator m_it = map.begin(); m_it != map.end(); m_it++)
	{
		std::cout << m_it->first<<" :\n";
		for (auto l_it : m_it->second)
		{
			std::cout << l_it << "\t";
		}
		DEL;
	}*/
	int emptyCount = 0;
	for (std::pair<std::string, std::list<std::string>> m_it : map) {
		if (m_it.second.empty())emptyCount++;
	}
	std::cout << "list size: " << map.size()<<" | empty: " << emptyCount << " | max size: " << map.max_size()
		<< "\n_________________________________________________________________________\n";
	for (std::pair<std::string, std::list<std::string>> m_it : map)
	{
		std::cout << m_it.first << " : ";
		if (m_it.second.empty())std::cout << "\t\t\t\t\t...empty...";
		else {
			
			for (std::list<std::string>::iterator l_it = m_it.second.begin(); l_it != m_it.second.end(); l_it)
			{
				std::cout << "\n\t" << *l_it;
				l_it++;
				if (l_it != m_it.second.end())std::cout << ",";
			}std::cout << ";";
		}
		DEL;
	}
	std::cout << "\n\n\t[Esc] Exit\n";
	
}

void printOne(const std::map<std::string, std::list<std::string>>& map)
{
	LIC_PLATE_INP
	std::cout << "\n\n";
	bool notFound = true;
	for (std::pair<std::string, std::list<std::string>> m_it : map)
	{
		if (m_it.first == licensePlate) {
			std::cout << m_it.first << " :\n";
			for (std::string l_it : m_it.second)
			{
				std::cout << "\t" << l_it<<"\n";
				notFound = false;
			}
			break;
		}
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Enter] Search\n";
	if(notFound)std::cout << "Такого номера нету в базе";

}

void save(const std::map<std::string, std::list<std::string>>& map)
{
	std::ofstream fout("base.txt");
	for (std::pair<std::string, std::list<std::string>> m_it : map)
	{
		fout << m_it.first << ":";
		for (std::string l_it : m_it.second)
		{
			fout << l_it << ",";
		}
		fout.seekp(-1, std::ios::cur);
		fout << ";\n";

	}
	fout.close();
	std::cout << "Database saves in file \"base.txt\" in project folder\n\n";
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Enter] Resave\n";
	system("start notepad base.txt");
}

std::map<std::string, std::list<std::string>> init()
{
	std::map<std::string, std::list<std::string>> PoliceDB =
	{
		std::pair<std::string,std::list<std::string>>
		("BI0000BI",{"превышение скорости","вождение в нетрезвом состоянии"}),

		std::pair<std::string,std::list<std::string>>
		("BI0001BI",{"езда по встречке"}),

		std::pair<std::string,std::list<std::string>>
		("BI0002BI",{"парковка в неположеном месте"}),

		std::pair<std::string,std::list<std::string>>
		("BI0003BI",{"проезд на красный","плюнул в полицейского"})
	};

	

	return PoliceDB;
}

void load(std::map<std::string, std::list<std::string>>& map)
{
	map.clear();
	std::cout << "Database is cleaned.\n\n";
	std::string licensePlate;
	std::string violation;
	std::list<std::string> violationList;

	std::ifstream fin("base.txt");

	if (fin.is_open())
	{
		bool firstLine = false;
		while (!fin.eof())
		{
			if(firstLine)std::getline(fin, licensePlate,'\n');
			firstLine = true;
			std::getline(fin, licensePlate,':');
			if (licensePlate == "")break;
			//std::cout << licensePlate << " : ";
			std::getline(fin, violation, ';');
			//std::cout << licensePlate << "\t" << violation << std::endl;
			boost::algorithm::split(violationList, violation, boost::is_any_of(","));
			//for (auto x : violationList)	std::cout << x<<"\t";	std::cout << std::endl;
			map.insert(
				std::pair<std::string, std::list<std::string>>
				(licensePlate, violationList)
			);
			if (violation.size() == 0)map[licensePlate].clear();
		}
		std::cout << "Database is loaded.\n\n";
	}
	else {
		std::cerr << "Error: file is not found";
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Enter] Reload\n";
}

void insert(std::map<std::string, std::list<std::string>>& map)	//add new
{
	LIC_PLATE_INP
	if (licensePlate.size() < 6) { std::cout << "\n\nВы не указали номер автомобиля."; }
	else {
		VIO_INP
		if (violation.size() < 10) { std::cout << "\n\nВы не указали правонарушение."; }
		else {
			std::map<std::string, std::list<std::string>>::iterator offender = map.find(licensePlate);

			if (offender != map.end())
			{
				offender->second.push_back(violation);
			}
			else
			{
				map.insert(std::pair<std::string, std::list<std::string>>(licensePlate, { violation }));
				std::cout << "\n\nДобавлен новый номер транспортного средства";
			}
			std::cout << "\n\nПравонарушение по указаному номеру успешно добавлено.";
		}
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Enter] Add new\n";
}

void removePair(std::map<std::string, std::list<std::string>>& map)		//erase
{
	LIC_PLATE_INP
	if (licensePlate.size() < 6) { std::cout << "\n\nВы не указали номер автомобиля."; }
	else {
		bool notFound = true;
		for (std::pair<std::string, std::list<std::string>> m_it : map)	if (m_it.first == licensePlate)	notFound = false;
		if (notFound)std::cout << "\n\nТакого номера нету в базе!";
		map.erase(licensePlate);
		std::cout << "\n\nНомер успешно удален из базы данных.";
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Enter] Erase\n";

}

void removeViol(std::map<std::string, std::list<std::string>>& map)
{
	LIC_PLATE_INP
	if (licensePlate.size() < 6) { std::cout << "\n\nВы не указали номер автомобиля."; }
	else {
		VIO_INP
		if (violation.size() < 10) { std::cout << "\n\nВы не указали правонарушение.";}
		else {
			bool notFoundLic = true;
			bool notFoundViol = true;
			for (std::pair<std::string, std::list<std::string>> m_it : map) {
				if (m_it.first == licensePlate) {
					notFoundLic = false;

					for (std::string l_it : m_it.second) {
						if (l_it == violation)notFoundViol = false;
					}
				}
			}
			if (notFoundLic)std::cout << "\n\nТакого номера нету в базе!";
			if (notFoundViol)std::cout << "\n\nЭто правонарушение не пренадлежит даному номеру автомобиля!\n\n";

			map[licensePlate].remove(violation);
			std::cout << "\n\nПравонарушение успешно удалено.";
		}
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Enter] Remove violation\n";
}

/*PoliceDB["BI 0001 BI"].remove("езда по встречке");
	PoliceDB.erase("BI 0000 BI");*/