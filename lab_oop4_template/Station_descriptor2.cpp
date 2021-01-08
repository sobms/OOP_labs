#include "pch.h"
#include "Station_descriptor2.h"
#include <iostream>
#include <typeinfo>
#include "../MyList/My_list.h"

namespace Metro_line {
	int get_value(int min, int max);
	std::ostream& operator << (std::ostream& out, const transition_descriptor& tr) {
		out << tr.line_name << " " << tr.station_name;
		return out;
	}
	std::istream& operator>> (std::istream& in, transition_descriptor& tr) {
		std::cout << "Enter line name: " << std::endl;
		in >> tr.line_name;
		std::cout << "Enter name of station: " << std::endl;
		in >> tr.station_name;
		return in;
	}
	std::ostream& Transfer_node::show_info(std::ostream& out) const {
		Station::show_info(out);
		std::cout << "Transitions: ";
		for (int i = 0; ((transitions[i].line_name.length() != 0) && (i < 3)); i++) {
			if (i == 0) {
				std::cout << transitions[i];
			}
			else {
				std::cout << ", " << transitions[i];
			}
		}
		return out;
	}
	std::ostream& Crossing_station::show_info(std::ostream& out) const {
		Station::show_info(out);
		std::cout << "Transition lines: ";
		for (int i = 0; ((transition_lines[i].length() != 0) && (i < 3)); i++) {
			if (i == 0) {
				out << transition_lines[i];
			}
			else {
				out << ", " << transition_lines[i];
			}
		}
		return out;
	};
	std::istream& Crossing_station::get(std::istream& in) {
		Station::get(in);
		int n;
		std::cout << "Enter_number of lines: " << std::endl;;
		n = get_value(0, 3);
		std::cout << "Enter transition lines: " << std::endl;
		for (int i = 0; i < n; i++) {
			std::string name;
			std::cin >> name;
			try {
				add_transition_line(name);
			}
			catch (std::logic_error& err1) {
				std::cout << err1.what() << std::endl;
			}
			catch (std::out_of_range& err2) {
				std::cout << err2.what() << std::endl;
			}
		}
		return in;
	}
	std::istream& Transfer_node::get(std::istream& in) {
		Station::get(in);
		int n;
		std::cout << "Enter_number of transitions: " << std::endl;;
		n = get_value(0, 3);
		std::cout << "Enter transitions: " << std::endl;
		for (int i = 0; i < n; i++) {
			transition_descriptor transition_name;
			std::cin >> transition_name;
			try {
				add_transition(transition_name);
			}
			catch (std::logic_error& err1) {
				std::cout << err1.what() << std::endl;
			}
			catch (std::out_of_range& err2) {
				std::cout << err2.what() << std::endl;
			}
		}
		return in;
	}
	Station* change_type(const Station* st) {//ввод типа во внешнюю функцию, тип в аргументы
		std::cout << "Enter type of station to change current type: " << std::endl;
		std::cout << "1. station without transition" << std::endl << "2. station with transition" << std::endl << "3. transfer node" << std::endl;
		int type = 0;
		type = get_value(0, 3);
		std::string name = st->get_name();
		delete st;
		Station a;
		Crossing_station b;
		Transfer_node c;
		switch (type) {
		case 1:
			st = &a;
			break;
		case 2:
			std::cout << "Enter number of transition lines->";
			int n;
			n = get_value(0, 3);
			std::cout << "Enter transition lines: " << std::endl;
			for (int i = 0; i < n; i++) {
				std::cout << "Enter name of transition line " << std::endl;
				std::string name;
				std::cin >> name;
				try {
					b.add_transition_line(name);
				}
				catch (std::logic_error& err1) {
					std::cout << err1.what() << std::endl;
				}
				catch (std::out_of_range& err2) {
					std::cout << err2.what() << std::endl;
				}
			}
			st = &b;
			break;
		case 3:
			std::cout << "Enter number of transitions->";
			n = get_value(0, 3);
			std::cout << "Enter transitions: " << std::endl;
			for (int i = 0; i < n; i++) {
				transition_descriptor transition_name;
				std::cin >> transition_name;
				try {
					c.add_transition(transition_name);
				}
				catch (std::logic_error& err1) {
					std::cout << err1.what() << std::endl;
				}
				catch (std::out_of_range& err2) {
					std::cout << err2.what() << std::endl;
				}
			}
			st = &c;
			break;
		}
		Station* res = st->copy();
		res->change_name(name);
		return res;
	}
	My_list<std::string> Crossing_station::get_transition_lines() const {
		My_list<std::string> res;
		for (int i = 0; ((transition_lines[i].length() != 0) && (i < 3)); i++) {
			res.push_back(transition_lines[i]);
		}
		return My_list<std::string>(res);
	}

	My_list <transition_descriptor> Transfer_node::get_transitions_list() const {
		My_list <transition_descriptor> res;
		for (int i = 0; ((transitions[i].line_name.length() != 0) && (i < 3)); i++) {
			res.push_back(transitions[i]);
		}
		return My_list<transition_descriptor>(res);
	}
	Crossing_station& Crossing_station::add_transition_line(std::string name) { //предупреждения во внешнюю функцию в обработку ошибок
		int i;
		//поиск существующей станции
		for (i = 0; ((transition_lines[i].length() != 0) && (i < 3)); i++) {
			if (transition_lines[i] == name) {
				throw std::logic_error("Transition line with this name already exist!");
				return *this;
			}
		}
		if (i >= 3) {
			throw std::out_of_range("transition lines array are already full");
		}
		else {
			transition_lines[i] = name;
		}
		return *this;
	}
	Station& Transfer_node::add_transition(transition_descriptor transition_name) { // обработка ошибок
		int i;
		for (i = 0; ((transitions[i].line_name.length() != 0) && (i < 3)); i++) {
			if ((transitions[i].line_name == transition_name.line_name) && (transitions[i].station_name == transition_name.station_name)) {
				throw std::logic_error("Transition with this name already exist!");
				return *this;
			}
		}
		if (i >= 3) {
			throw std::out_of_range("transition array are already full");
		}
		else {
			transitions[i] = transition_name;
		}
		return *this;
	}

}