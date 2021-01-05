#include "pch.h"
#include <iostream>
#include "Line_descriptor.h"
#include "../Station_discriptors/Station_discriptors.h"
#include <string.h>
#include <string>
#include <typeinfo>
#include <list>
#include <algorithm>
#include <Windows.h>

namespace Metro_line {
	int get_value(int min, int max) {
		while (true)
		{
			int a;
			std::cin >> a;
			system("cls");
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "Oops, that input is invalid. Please try again.\n";
			}
			else
			{
				std::cin.ignore(32767, '\n');
				if ((a<=max)||(a>min)) {
					return a;
				}
				else {
					std::cout << "Type don't exist. Try again!\n";
				}
			}
		}
	}
	void Line_descriptor::insert(Station* new_elem) {//вывод ввода имени линии в начало создания линии, 
		std::list<Station*>::iterator it;

		if (station_table.empty()) {
			station_table.push_front(new_elem);
			std::cout << "Enter name of metro line" << std::endl;
			std::cin >> name;
			std::cin.ignore(80, '\n');
		}
		else {
			int success = 0;
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

				if (name_next_station == "end") { station_table.push_back(new_elem); return; }

				for (it = station_table.begin(); it != station_table.end(); it++) {
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
			station_table.insert(it, new_elem);
		}
	}
	Line_descriptor& Line_descriptor::add_station() // сделать полностью внешней функцией
	{
		std::cout << "Enter type of station:" << std::endl << "1. station without transition" << std::endl << "2. station with transition" << std::endl << "3. transfer node" << std::endl;
		int type = 0;
		type = get_value(0,3);

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
		Line_descriptor::insert(new_station->copy());
		return *this;
	}

	int Line_descriptor::remove_station(std::string name) {
		std::list<Station*>::iterator it;
		for (it = station_table.begin(); it != station_table.end(); it++) {
			if ((*it)->get_name() == name) {
				delete (*it);
				station_table.erase(it);
				return true;
			}
		}
		return false;
	}
	void Line_descriptor::replace_station(std::string name, Station* sample) {
		std::list<Station*>::iterator it;
		for (it = station_table.begin(); it != station_table.end(); it++) {
			if ((*it)->get_name() == name) {
				delete (*it);
				it = station_table.erase(it);
				station_table.insert(it, sample);
				return;
			}
		}
	}
	Station* Line_descriptor::find(std::string name) const
	{
		std::list<Station*>::const_iterator it;
		for (it = station_table.begin(); it != station_table.end(); it++) {
			if ((*it)->get_name() == name) {
				return (*it)->copy();
			}
		}
		return nullptr;
	}


	void Line_descriptor::show_table()
	{
		std::list<Station*>::iterator it;

		std::cout << "Name of metro line: " << name << std::endl;
		
		std::cout << "List of station:" << std::endl;
		for (it = station_table.begin(); it != station_table.end(); it++) {
			std::cout << (*it)->get_name() << std::endl;
		}
	}
	Line_descriptor::~Line_descriptor() {
		std::list<Station*>::iterator it;
		for (it = station_table.begin(); it != station_table.end(); it++) {
			delete (*it);
		}
		station_table.clear();
		name.clear();
	}

	Line_descriptor::Line_descriptor(const Line_descriptor& sample)
	{
		std::list<Station*>::const_iterator it;
		for (it = sample.station_table.begin(); it != sample.station_table.end(); it++) {
			station_table.push_back(*it);
		}
		name = sample.name;
	}
	Line_descriptor& Line_descriptor::operator = (const Line_descriptor& sample) {
		std::list<Station*>::const_iterator it;
		if (this != &sample) {
			// удаление объекта слева от присваивания
			for (it = station_table.begin(); it != station_table.end(); it++) {
				delete (*it);
			}
			station_table.clear();
			name.clear();
			// копирование данных из правого объекта в левый
			for (it = sample.station_table.begin(); it != sample.station_table.end(); it++) {
				station_table.push_back(*it);
			}
			name = sample.name;
		}
		return *this;
	}
	Line_descriptor::Line_descriptor(Line_descriptor&& sample) {
		station_table.splice(station_table.begin(), sample.station_table);
		name = sample.name;
		sample.name.clear();
	}
	Line_descriptor& Line_descriptor::operator = (Line_descriptor&& sample) {
		std::list<Station*>::const_iterator it;
		if (this != &sample) {
			// очищаем левую часть
			name.clear();
			for (it = station_table.begin(); it != station_table.end(); it++) {
				delete (*it);
			}
			station_table.clear();
			// перемещаем объект, стоящий справа от присваивания
			station_table.splice(station_table.begin(), sample.station_table);
			name = sample.name;
			sample.name.clear();
		}
		return *this;
	}
}