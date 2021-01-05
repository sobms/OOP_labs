#pragma once
#include "../Station_discriptors/Station_discriptors.h"
#include <list>
namespace Metro_line {

	class Line_descriptor
	{
	private:
		std::string name;
		std::list <Station*> station_table;
		void insert(Station* new_elem);
	public:
		Line_descriptor(std::string default_name = "undefined") : name(default_name) {} // empty constructor???

		Line_descriptor(const Line_descriptor& line); // copy constructor
		Line_descriptor(Line_descriptor&& line); // move constructor
		Line_descriptor& operator = (const Line_descriptor& second); // copy assignment
		Line_descriptor& operator = (Line_descriptor&& line); // move assignment
		~Line_descriptor(); //destructor
		
		int remove_station(std::string name);
		void replace_station(std::string name, Station* sample);
		std::string get_name() const { return name; }				
		Line_descriptor& add_station();
		Station* find(std::string name) const;
		void show_table();
	};
}
