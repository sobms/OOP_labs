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
				if ((a<=max)&&(a>min)) {
					return a;
				}
				else {
					std::cout << "Value is out of range. Try again!\n";
				}
			}
		}
	}
	void Line_descriptor::insert(Station* new_elem, std::list<Station*>::iterator it) {
		if (station_table.empty()) {
			station_table.push_front(new_elem->copy());
		}
		else {
			if (!find(new_elem->get_name())){
				station_table.insert(it, new_elem);
			}
			else {
				throw std::exception("Element already exist");
			}
		}
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
		if (!sample) {
			throw std::invalid_argument("The value of station for replacement is nullptr");
		}
		else {
			for (it = station_table.begin(); it != station_table.end(); it++) {
				if ((*it)->get_name() == name) {
					delete (*it);
					it = station_table.erase(it);
					station_table.insert(it, sample);
					return;
				}
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
	Station* Line_descriptor::find_by_transition(std::string name) const
	{
		Transfer_node* ptr;
		std::list<Station*>::const_iterator it;
		std::list<transition_descriptor>::iterator iter;
		for (it = station_table.begin(); it != station_table.end(); it++) {
			if (typeid(*(*it)) == typeid(Transfer_node)) {
				ptr = dynamic_cast<Transfer_node*>((*it)->copy());
				std::list<transition_descriptor> tr_lst = ptr->get_transitions_list();
				for (iter = tr_lst.begin(); iter != tr_lst.end(); iter++) {
					if ((*iter).station_name == name) {
						return (*it)->copy();
					}
				}
				delete ptr;
				tr_lst.clear();
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
			station_table.push_back((*it)->copy());
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
				station_table.push_back((*it)->copy());
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