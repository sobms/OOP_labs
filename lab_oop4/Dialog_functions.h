#pragma once
#include "../Station_discriptors/Station_discriptors.h"
#include "../Metro_line/Line_descriptor.h"
#include <typeinfo>

namespace Metro_line {
	int get_value(int min, int max);

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
				try {
					station->add_transition_line();
				}
				catch (std::out_of_range& err) {
					std::cout << err.what() << std::endl;
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
				try {
					station->add_transition();
				}
				catch (std::out_of_range& err) {
					std::cout << err.what() << std::endl;
				}
				break;
		}
		return station;
	}
	void Add(Line_descriptor& line) {
		//вынести ввод типа станции
		line.Line_descriptor::add_station();
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

	}
	void Show_line(Line_descriptor& line) {
		line.Line_descriptor::show_table();
	}
}