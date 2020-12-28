#pragma once
#include "pch.h"
#include <iostream>
#include <typeinfo>

namespace Metro_line {
	class Station_descriptor { // abstract class
	protected:
		virtual std::ostream& show_info(std::ostream& out) const = 0;
	public:
		virtual std::string& get_name() const = 0;
		virtual Station_descriptor& change_name() = 0;
		virtual std::string& get_type() const = 0;
		virtual Station_descriptor& change_type() = 0;
		virtual Station_descriptor* copy() const;
		friend std::ostream& operator << (std::ostream& out, const Station_descriptor& sample) {
			sample.show_info(out);
		}
	};
	class Station : public Station_descriptor { // station without transition
	protected:
		std::string name;
		virtual std::ostream& show_info(std::ostream& out) const {
			std::cout << "Station name: " << name;
		};
	public:
		Station(std::string default_name = "undefined") :
			name(default_name) {}

		std::string& get_name() const;
		Station& change_name();
		std::string& get_type() const;
		Station& change_type();
		Station* copy() const {
			return new Station(*this);
		}
	};
	class Crossing_station : public Station_descriptor { // station with transition
	protected:
		std::string name;
		std::string transition_lines[3];
		virtual std::ostream& show_info(std::ostream& out) const {
			std::cout << "Station name: " << name << std::endl;
			std::cout << "Transition lines: ";
			for (int i = 0; transition_lines[i].length() != 0; i++) {
				std::cout << transition_lines[i] << " ";
			}
		};
	public:
		Crossing_station(std::string default_name = "undefined") :
			name(default_name) {}

		std::string& get_name() const;
		Crossing_station& change_name();
		std::string& get_type() const;
		Crossing_station& change_type();
		Crossing_station* copy() const {
			return new Crossing_station(*this);
		}

		std::string* get_transition_lines() const;
		Crossing_station& add_transition_line();
	};

	struct transition_descriptor {
		std::string line_name;
		std::string station_name;
	};

	class Transfer_node : public Station_descriptor { //transfer node
	protected:
		std::string name;
		transition_descriptor transitions[3];
		virtual std::ostream& show_info(std::ostream& out) const;
	public:
		Transfer_node(std::string default_name = "undefined") :
			name(default_name) {}

		std::string& get_name() const;
		Transfer_node& change_name();
		std::string& get_type() const;
		Transfer_node& change_type();
		Transfer_node* copy() const {
			return new Transfer_node(*this);
		}
		Transfer_node& add_transition();
		transition_descriptor* get_tranitions_list() const;

	};
}