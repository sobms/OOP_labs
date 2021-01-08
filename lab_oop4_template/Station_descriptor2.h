#pragma once
#include "pch.h"
#include <iostream>
#include <typeinfo>
#include "../MyList/My_list.h"

namespace Metro_line {
	class Station { // station without transition
	private:
		std::string name;
	protected:
		virtual std::ostream& show_info(std::ostream& out) const {
			std::cout << "Station name: " << name << std::endl;
			return out;
		};
		virtual std::istream& get(std::istream& in) {
			std::cout << "Enter name of station" << std::endl;
			in >> name;
			return in;
		}
	public:
		Station(std::string default_name = "undefined") :
			name(default_name) {}

		std::string get_name() const { return name; };
		Station& change_name(const std::string& name2) { name = name2; return *this; };
		std::string get_type() const { return typeid(*this).name(); }
		friend Station* change_type(const Station* st);
		virtual Station* copy() const {
			return new Station(*this);
		}
		friend std::ostream& operator << (std::ostream& out, const Station& sample) {
			sample.show_info(out);
			return out;
		}
		friend std::istream& operator >> (std::istream& in, Station& sample) {
			sample.get(in);
			return in;
		}
	};
	class Crossing_station : public Station { // station with transition
	private:
		std::string transition_lines[3];
	protected:
		virtual std::ostream& show_info(std::ostream& out) const;
		virtual std::istream& get(std::istream& in);
	public:
		Crossing_station(std::string name = "undefined") : Station(name) {}
		Crossing_station(std::string lines[3], std::string name = "undefined") : Station(name)
		{
			for (int i = 0; i < 3; i++) {
				transition_lines[i] = lines[i];
			}
		}
		Crossing_station* copy() const {
			return new Crossing_station(*this);
		}

		My_list<std::string> get_transition_lines() const;
		Crossing_station& add_transition_line(std::string name);
	};

	struct transition_descriptor {
		std::string line_name;
		std::string station_name;
	};

	class Transfer_node : public Station { //transfer node
	private:
		transition_descriptor transitions[3];
	protected:
		virtual std::ostream& show_info(std::ostream& out) const;
		virtual std::istream& get(std::istream& in);
	public:
		Transfer_node(std::string default_name = "undefined") : Station(default_name) {}

		Transfer_node(transition_descriptor tr[3], std::string default_name = "undefined") : Station(default_name)
		{
			for (int i = 0; i < 3; i++) {
				transitions[i] = tr[i];
			}
		}

		friend std::ostream& operator << (std::ostream out, const transition_descriptor& tr);

		Transfer_node* copy() const {
			return new Transfer_node(*this);
		}
		Station& add_transition(transition_descriptor transition_name);
		My_list <transition_descriptor> get_transitions_list() const;

	};
}
