#pragma once
#include "../Station_descriptor2/Station_descriptor2.h"
#include "../MyList/My_list.h"
namespace Metro_line {

	class Line_descriptor
	{
	private:
		std::string name;
		My_list <Station*> station_table;
	public:
		Line_descriptor(std::string default_name = "undefined") : name(default_name) {} // empty constructor

		Line_descriptor(const Line_descriptor& line); // copy constructor
		Line_descriptor(Line_descriptor&& line); // move constructor
		Line_descriptor& operator = (const Line_descriptor& second); // copy assignment
		Line_descriptor& operator = (Line_descriptor&& line); // move assignment
		~Line_descriptor(); //destructor

		Station* find_by_transition(std::string name) const;
		int remove_station(std::string name);
		void replace_station(std::string name, Station* sample);
		std::string get_name() const { return name; }
		void insert(Station* new_elem, My_list<Station*>::Iterator it);
		Station* find(std::string name) const;
		void show_table();
		My_list<Station*>::Iterator iter_begin() {
			return station_table.begin();
		}
		My_list<Station*>::Iterator iter_end() {
			return station_table.end();
		}
		bool is_line_empty() {
			return station_table.empty();
		}

	};
}

