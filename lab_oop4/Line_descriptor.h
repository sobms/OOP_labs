#pragma once
#include "../Station_discriptors/Station_discriptors.h"
namespace Metro_line {
	typedef struct Table {
		Station_descriptor* data;
		Table* next;
	};

	class Line_descriptor
	{
	private:
		std::string name;
		Table* station_table;
	public:
		Line_descriptor() {
			station_table = nullptr;
		}
		Line_descriptor(const Line_descriptor& line);
		Line_descriptor& operator = (const Line_descriptor& second);
		~Line_descriptor();
		
		std::string& get_name() const;
		Station& add_station();
		Station* find() const;
		void show_table() const;
	};
}
