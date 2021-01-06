#pragma once
#include "../Station_discriptors/Station_discriptors.h"
#include "../Metro_line/Line_descriptor.h"
#include <typeinfo>
#include <Windows.h>

namespace Metro_line {
	int get_value(int min, int max);
	std::istream& operator>> (std::istream& in, transition_descriptor& tr);
	std::string get_str() {
		std::string name;
		do {
			std::cin >> name;
			if (!std::cin.good()) {
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "Input error. Please try again."<<std::endl;
			}
			else { return name; }
		} while (true);
	}
	Crossing_station* Modify_crossing_station(Crossing_station* station) {
		std::cout << "Enter number of function: " << std::endl << "1. Change name" << std::endl << "2. Add transition line" << std::endl;
		int option_type = 0;
		option_type = get_value(0,2);
		std::string name;
		switch (option_type) {
			case 1:
				std::cout << "Enter new name: ";
				name = get_str();
				station->Station::change_name(name);
				break;
			case 2:
				std::cout << "Enter name of transition line " << std::endl;
				std::string name;
				std::cin >> name;
				try {
					station->add_transition_line(name);
				}
				catch (std::logic_error& err1) {
					std::cout << err1.what() << std::endl;
				}
				catch (std::out_of_range& err2) {
					std::cout << err2.what() << std::endl;
				}
				break;
		}	
		return station;
	}
	Station* Modify_station(Station* station) {
		std::cout << "Enter number of function: " << std::endl << "1. Change name" << std::endl;
		int option_type = 0;
		option_type = get_value(0,1);
		std::string name;
		switch (option_type) {
			case 1:
				std::cout << "Enter new name: ";
				name = get_str();
				station->Station::change_name(name);
				break;
		}
		return station;
	}
	Transfer_node* Modify_transfer_node(Transfer_node* station) {
		std::cout << "Enter number of function: " << std::endl << "1. Change name" << std::endl << "2. Add transition" << std::endl;
		int option_type = 0;
		option_type = get_value(0,2);
		std::string name;
		switch (option_type) {
			case 1:
				std::cout << "Enter new name: ";
				name = get_str();
				station->Station::change_name(name);
				break;
			case 2:
				transition_descriptor transition_name;
				std::cin >> transition_name;
				try {
					station->add_transition(transition_name);
				}
				catch (std::logic_error& err1) {
					std::cout << err1.what() << std::endl;
				}
				catch (std::out_of_range& err2) {
					std::cout << err2.what() << std::endl;
				}
				break;
		}
		return station;
	}

	Line_descriptor& add_station(Line_descriptor& line) // сделать полностью внешней функцией
	{
		//формируем станцию нужного типа
		std::cout << "Enter type of station:" << std::endl << "1. station without transition" << std::endl << "2. station with transition" << std::endl << "3. transfer node" << std::endl;
		int type = 0;
		type = get_value(0, 3);

		Station a;
		Crossing_station b;
		Transfer_node c;

		Station* new_station = nullptr;
		switch (type) {
		case 1:
			new_station = &a;
			break;
		case 2:
			new_station = &b;
			break;
		case 3:
			new_station = &c;
			break;
		}
		std::cin >> (*new_station);
		std::cin.ignore(80, '\n');

		//находим необходимое значение итератора
		std::list<Station*>::iterator it;
		int success = 0;
		if (!line.is_line_empty()) {
			do {
				system("cls");
				std::cout << "Enter name of station before you want to create a new station or enter 'end' to add station at the and of line: ";
				std::string name_next_station;
				std::cin >> name_next_station;
				if (!std::cin.good()) {
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					std::cout << "Input error. Please try again." << std::endl;
					Sleep(2000);
					continue;
				}

				if (name_next_station == "end") { it = line.Line_descriptor::iter_end(); break; }

				for (it = line.Line_descriptor::iter_begin(); it != line.Line_descriptor::iter_end(); it++) {
					if ((*it)->get_name() == name_next_station) {
						success = 1;
						break;
					}
				}
				if (!success) {
					std::cout << "Station_not_exist. Please try again!" << std::endl;
					Sleep(2000);
				}
			} while (!success);
		}
		try {
			line.Line_descriptor::insert(new_station->copy(), it);
		}
		catch (std::exception& err) {
			std::cout << err.what() << std::endl;
			return line;
		}
		return line;
	}
	void Add(Line_descriptor& line) {
		line = add_station(line);
	}
	void Remove(Line_descriptor& line) {
		std::cout << "Enter name of station that's necessary to remove" << std::endl;
		std::string name = get_str();
		int res = line.remove_station(name);
		if (res) {
			std::cout << "Success!" << std::endl;
		}
		else {
			std::cout << "Station not exist!" << std::endl;
		}

	}
	void Change(Line_descriptor& line) {
		std::cout << "Enter name of station to modify" << std::endl;
		std::string name = get_str();

		Station* obj = line.find(name);
		if (!obj) {
			std::cout << "Station with this name don't exist!" << std::endl;
			return;
		}
		std::cout << "If you want change type of station enter 'yes' else enter any simbol" << std::endl;
		std::string choice = get_str();
		if (choice == "yes") {
			obj = change_type(obj);
			line.Line_descriptor::replace_station(name, obj);
			return;
		}
		Crossing_station* cros_station;
		Transfer_node* trans_node;
		// вычисляем тип станции и вызываем нужные функции модификации
		if (typeid(*obj) == typeid(Crossing_station))
		{
			cros_station = dynamic_cast<Crossing_station*>(obj);
			cros_station = (Modify_crossing_station(cros_station));
			Station* s = cros_station;
			line.Line_descriptor::replace_station(name, s);
		}
		else if (typeid(*obj) == typeid(Transfer_node))
		{
			trans_node = dynamic_cast<Transfer_node*>(obj);
			trans_node = (Modify_transfer_node(trans_node));
			Station* s = trans_node;
			line.Line_descriptor::replace_station(name, s);
		} 
		else {
			obj = Modify_station(obj);
			line.Line_descriptor::replace_station(name, obj);
		}
	}
	void Find(Line_descriptor& line) {
		std::cout << "Enter name of station that's necessary to find" << std::endl;
		std::string name = get_str();
		// поиск станции
		Station* obj = line.find(name);
		// вывод информации о станции
		if (!obj) {
			std::cout << "Station not found!" << std::endl;
		}
		else {
			std::cout << (*obj);
		}
	}
	void Find_by_name_transfer_station(Line_descriptor& line) {
		std::cout << "Enter name of transfer_station which has access to searchable station" << std::endl;
		std::string name = get_str();
		Station* obj = line.find_by_transition(name);
		if (!obj) {
			std::cout << "Station not found!" << std::endl;
		}
		else {
			std::cout << (*obj);
		}
	}
	void Show_line(Line_descriptor& line) {
		line.Line_descriptor::show_table();
	}
}