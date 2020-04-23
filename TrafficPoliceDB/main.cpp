#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<Windows.h>
#include<array>
#include<conio.h>
#include<boost/algorithm/string.hpp>


const int MENU_SIZE = 11;

#define DEL std::cout<<"\n-------------------------------------------------------\n"

#define LIC_PLATE_INP	std::cout << "Введите номер транспортного средства: ";	std::string licensePlate;	SetConsoleCP(1251);		std::getline(std::cin, licensePlate);	SetConsoleCP(866);		
#define VIO_INP			std::cout << "Введите правонарушение: ";				std::string violation;		SetConsoleCP(1251);		std::getline(std::cin, violation);		SetConsoleCP(866);			

void printFullMap(const std::map<std::string, std::list<std::string>>& map);
void printOne(const std::map<std::string, std::list<std::string>>& map);

std::map<std::string, std::list<std::string>> init();
void insert(std::map<std::string, std::list<std::string>>& map);

void removePair(std::map<std::string, std::list<std::string>>& map);
void removeViol(std::map<std::string, std::list<std::string>>& map);

void save(const std::map<std::string, std::list<std::string>>& map);
void load(std::map<std::string, std::list<std::string>>& map);

void menu();
void printMenu(std::array<bool, MENU_SIZE> optionActive);

std::list<std::string> EventList;

void printEL();
void loadEL();
void saveEL();


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
	std::array<bool, MENU_SIZE> optionActive = { true,false,false,false,false,false,false,false,false,false,false };
	char key = 72;
	while (key != 27) {
		system("cls");
		printMenu(optionActive);
		key = _getch();
		for (int i = 0; i < optionActive.size(); i++)
		{
			if ((key == 72 || key == 80) && optionActive[i]) {
				optionActive[i] = false;
				if (key == 72) { i == 0 ? optionActive[optionActive.size() - 1] = true : optionActive[i - 1] = true; }
				else if (key == 80) { (i == optionActive.size() - 1) ? optionActive[0] = true : optionActive[i + 1] = true; }
				i = optionActive.size();
			}
			else if (optionActive[i] && ((key > 47 && key < 58) || key == 45)) {
				optionActive[i] = false;
				switch (char(key))
				{
				case '1':optionActive[0] = true; break;
				case '2':optionActive[1] = true; break;
				case '3':optionActive[2] = true; break;
				case '4':optionActive[3] = true; break;
				case '5':optionActive[4] = true; break;
				case '6':optionActive[5] = true; break;
				case '7':optionActive[6] = true; break;
				case '8':optionActive[7] = true; break;
				case '9':optionActive[8] = true; break;
				case '0':optionActive[9] = true; break;
				case '-':optionActive[10] = true; break;
				default:
					break;
				}
				i = optionActive.size();
			}
			if (key == 13) {
				system("cls");
				do {
					if (optionActive[0])	printFullMap(PoliceDB);
					if (optionActive[1])	printOne(PoliceDB);
					if (optionActive[2])	insert(PoliceDB);
					if (optionActive[3])	removePair(PoliceDB);
					if (optionActive[4])	removeViol(PoliceDB);
					if (optionActive[5])	load(PoliceDB);
					if (optionActive[6])	save(PoliceDB);

					if (optionActive[7])	printEL();
					if (optionActive[8])	saveEL();
					if (optionActive[9])	loadEL();
					if (optionActive[10]) {
						EventList.clear(); std::cout << "\n\nЖурнал событий очищен"; std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Clean\n";
					}
					key = _getch();		system("cls");
				} while (key != 27);
				key = 0;
			}
		}
	};
}

void printMenu(std::array<bool, MENU_SIZE> optionActive)
{
	std::cout << "\n\n";
	std::array<std::pair<std::string, std::string>, MENU_SIZE> menuOptions = {
		std::pair<std::string,std::string>
		("\t\t>>>>>\tPRINT FULL DB\t<<<<<\n","\t\t\tPRINT FULL DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tPRINT ONE\t<<<<<\n","\t\t\tPRINT ONE\n"),

		std::pair<std::string,std::string>
		("\t\t>>>>>\tADD NEW\t\t<<<<<\n","\t\t\tADD NEW\n"),

		std::pair<std::string,std::string>
		("\t\t>>>>>\tERASE\t\t<<<<<\n","\t\t\tERASE\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tREMOVE VIOL\t<<<<<\n","\t\t\tREMOVE VIOL\n"),

		std::pair<std::string,std::string>
		("\t\t>>>>>\tLOAD DB\t\t<<<<<\n","\t\t\tLOAD DB\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tSAVE DB\t\t<<<<<\n","\t\t\tSAVE DB\n"),

		std::pair<std::string,std::string>
		("\t\t>>>>>\tPRINT EL\t<<<<<\n","\t\t\tPRINT EL\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tSAVE EL\t\t<<<<<\n","\t\t\tSAVE EL\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tLOAD EL\t\t<<<<<\n","\t\t\tLOAD EL\n"),
		std::pair<std::string,std::string>
		("\t\t>>>>>\tCLEAN EL\t<<<<<\n","\t\t\tCLEAN EL\n")
	};																	//11
	std::cout << "\n\t\t~~~ Traffic Police Database ~~~\n\n";
	for (int i = 0; i < menuOptions.size(); i++)
	{
		if (optionActive[i]) {
			std::cout << menuOptions[i].first;
		}
		else
		{
			std::cout << menuOptions[i].second;
		}
		if (i == 6)
		{
			std::cout << "\n";
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
			std::cout << l_it <<"\t";
		}
		DEL;
	}*/
	int emptyCount = 0;
	for (std::pair<std::string, std::list<std::string>> m_it : map) {
		if (m_it.second.empty())emptyCount++;
	}
	std::cout << "list size: " << map.size() << " | empty: " << emptyCount << " | max size: " << map.max_size()
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
	EventList.push_back("База данных напечатана");

	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Print\n";

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
			if (m_it.second.empty())std::cout << "\t...empty...";
			else {
				for (std::string l_it : m_it.second)
				{
					std::cout << "\t" << l_it << "\n";
					notFound = false;
					EventList.push_back("Напечатаны правонарушения по номеру: " + licensePlate);
				}
			}
			break;
		}
	}
	if (notFound)std::cout << "Такого номера нету в базе";
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Search\n";

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
	EventList.push_back("База данных сохранена");
	std::cout << "Database saved in file \"base.txt\" in project folder\n\n";
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Resave\n";
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
	EventList.push_back("База данных проинициализирована");
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
			if (firstLine)std::getline(fin, licensePlate, '\n');
			firstLine = true;
			std::getline(fin, licensePlate, ':');
			if (licensePlate == "")break;
			//std::cout << licensePlate <<" : ";
			std::getline(fin, violation, ';');
			//std::cout << licensePlate <<"\t" << violation << std::endl;
			boost::algorithm::split(violationList, violation, boost::is_any_of(","));
			//for (auto x : violationList)	std::cout << x<<"\t";	std::cout << std::endl;
			map.insert(
				std::pair<std::string, std::list<std::string>>
				(licensePlate, violationList)
			);
			if (violation.size() == 0)map[licensePlate].clear();
		}
		EventList.push_back("База данных загружена");
		std::cout << "Database is loaded.\n\n";
	}
	else {
		EventList.push_back("Файл загрузки небыл найден");
		std::cerr << "Error: file is not found";
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Reload\n";
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
						EventList.push_back("Добавлен новый номер транспортного средства");
						std::cout << "\n\nДобавлен новый номер транспортного средства.";
					}
					EventList.push_back("Добавлено правонарушение по номеру: " + licensePlate);
					std::cout << "\n\nПравонарушение по указаному номеру успешно добавлено.";
				}
		}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Add new\n";
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
			EventList.push_back("Удалён номер: " + licensePlate);
			std::cout << "\n\nНомер успешно удален из базы данных.";
		}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Erase\n";

}

void removeViol(std::map<std::string, std::list<std::string>>& map)
{
	LIC_PLATE_INP
		if (licensePlate.size() < 6) { std::cout << "\n\nВы не указали номер автомобиля."; }
		else {
			VIO_INP
				if (violation.size() < 10) { std::cout << "\n\nВы не указали правонарушение."; }
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
					EventList.push_back("Удалено правонарушение по номеру: " + licensePlate);
					std::cout << "\n\nПравонарушение успешно удалено.";
				}
		}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Remove violation\n";
}


void printEL()
{
	std::cout << "events: " << EventList.size() << " | "
		<< "\n_______________________________________________________________\n";
	for (std::string ev : EventList)
	{
		std::cout << "\n\t" << ev;
		if (EventList.size() < 20)std::cout << "\n";
	}
	EventList.push_back("Журнал событий просмотрен");
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Refresh\n";
}

void loadEL()
{
	EventList.clear();
	std::string event;

	std::ifstream fin("evlist.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::getline(fin, event, '\n');
			std::cout << event << "\n";
			EventList.push_back(event);
		}
		EventList.push_back("Журнал событий загружен");
		std::cout << "\n\nЖурнал событий загружен";
	}
	else {
		EventList.push_back("Файл загрузки небыл найден");
		std::cerr << "Error: file is not found";
	}
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Reload\n";
}

void saveEL()
{
	std::ofstream fout("evlist.txt");
	int count = 0;
	for (std::string ev : EventList)
	{
		fout << ev;
		if (count < EventList.size()-1) {
			fout << "\n"; count++;
		}
	}
	fout.seekp(-10, std::ios::cur);
	fout.close();
	EventList.push_back("Журнал событий сохранён");
	std::cout << "\n\nЖурнал событий сохранён";
	std::cout << "\n\n\t[Esc] Exit\t\t\t[Any key] Resave\n";
}