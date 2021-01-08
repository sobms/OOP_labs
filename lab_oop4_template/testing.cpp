#include <iostream>
#include "../Station_descriptor2/Station_descriptor2.h"
#include "../Line_desriptor2/Line_descriptor2.h"
#include "gtest/gtest.h"
#include "../MyList/My_list.h"
#include <typeinfo>
namespace LM = Metro_line;
bool comparison(LM::Station* a, LM::Station* b) {
	if (a->get_name() == b->get_name()) {
		if (a->get_type() == b->get_type()) {
			if (typeid(*a) == typeid(LM::Crossing_station)) {
				LM::Crossing_station* c_a = dynamic_cast<LM::Crossing_station*>(a);
				LM::Crossing_station* c_b = dynamic_cast<LM::Crossing_station*>(b);
				LM::My_list<std::string> lst1 = c_a->get_transition_lines();
				LM::My_list<std::string> lst2 = c_b->get_transition_lines();
				LM::My_list<std::string>::Iterator it1 = lst1.begin();
				LM::My_list<std::string>::Iterator it2 = lst2.begin();
				int i = 0;
				for (; it1 != lst1.end(), it2 != lst2.end(); it1++) {
					if ((*it1)->info != (*it2)->info) {
						return false;
					}
					it2++;
				}
				return true;
			}
			if (typeid(*a) == typeid(LM::Transfer_node)) {
				LM::Transfer_node* t_a = dynamic_cast<LM::Transfer_node*>(a);
				LM::Transfer_node* t_b = dynamic_cast<LM::Transfer_node*>(b);
				LM::My_list<LM::transition_descriptor> lst1 = t_a->get_transitions_list();
				LM::My_list<LM::transition_descriptor> lst2 = t_b->get_transitions_list();
				LM::My_list<LM::transition_descriptor>::Iterator it1 = lst1.begin();
				LM::My_list<LM::transition_descriptor>::Iterator it2 = lst2.begin();
				int i = 0;
				for (; it1 != lst1.end(), it2 != lst2.end(); it1++) {
					if (((*it1)->info.line_name != (*it2)->info.line_name) || (((*it1)->info.station_name) != ((*it2)->info.station_name))) {
						return false;
					}
					it2++;
				}
				return true;
			}
			if (typeid(*a) == typeid(LM::Station)) {
				return true;
			}
		}
	}
	return false;
}

TEST(Station_class, empty_constructor) {
	LM::Station s;
	ASSERT_EQ(s.get_name(), "undefined");
}
TEST(Station_class, initialize_constructor) {
	LM::Station s("station1");
	ASSERT_EQ(s.get_name(), "station1");
}
TEST(Station_class, change_name) {
	LM::Station s;
	s.change_name("new_name");
	ASSERT_EQ(s.get_name(), "new_name");
}
TEST(Station_class, get_type) {
	LM::Station s;
	ASSERT_EQ(s.get_type(), typeid(LM::Station).name());
}

TEST(Crossing_station_class, empty_constructor) {
	LM::Crossing_station c;
	ASSERT_EQ(c.get_name(), "undefined");
	LM::My_list<std::string> lst = c.get_transition_lines();
	LM::My_list<std::string>::Iterator it = lst.begin();
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info, "");
	}
}

TEST(Crossing_station_class, initialize_constructor1) {
	LM::Crossing_station c("station2");
	ASSERT_EQ(c.get_name(), "station2");
	LM::My_list<std::string> lst = c.get_transition_lines();
	LM::My_list<std::string>::Iterator it = lst.begin();
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info, "");
	}
}

TEST(Crossing_station_class, initialize_constructor2) {
	std::string mas[3] = {
		"red", "green", ""
	};
	LM::Crossing_station c(mas, "station2");
	ASSERT_EQ(c.get_name(), "station2");
	LM::My_list<std::string> lst = c.get_transition_lines();
	LM::My_list<std::string>::Iterator it = lst.begin();
	int i = 0;
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info, mas[i]);
		i++;
	}
}
TEST(Crossing_station_class, get_transition_lines) {
	std::string mas[3] = {
		"yellow", "green", "blue"
	};
	LM::Crossing_station c(mas, "station2");
	LM::My_list<std::string> lst = c.get_transition_lines();
	LM::My_list<std::string>::Iterator it = lst.begin();
	int i = 0;
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info, mas[i]);
		i++;
	}
}
TEST(Crossing_station_class, add_transition_line) {
	std::string mas[3] = {
		"yellow", "", ""
	};
	LM::Crossing_station c(mas, "station2");
	c.add_transition_line("silver");         // test function
	c.add_transition_line("red");         // test function
	LM::My_list<std::string> lst = c.get_transition_lines();
	LM::My_list<std::string>::Iterator it = lst.begin();
	int i = 0;
	std::string mas2[3] = { "yellow", "silver", "red" };
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info, mas2[i]);
		i++;
	}
}
TEST(Crossing_station_class, add_transition_line_err1) {
	std::string mas[3] = {
		"yellow", "grey", "blue"
	};
	LM::Crossing_station c(mas, "station2");
	ASSERT_THROW(c.add_transition_line("silver"), std::out_of_range);
}
TEST(Crossing_station_class, add_transition_line_err2) {
	std::string mas[3] = {
		"yellow", "grey", ""
	};
	LM::Crossing_station c(mas, "station2");
	ASSERT_THROW(c.add_transition_line("yellow"), std::logic_error);
}

TEST(Crossing_station_class, get_type) {
	LM::Crossing_station c;
	ASSERT_EQ(c.get_type(), typeid(LM::Crossing_station).name());
}

TEST(Transfer_node_class, empty_constructor) {
	LM::Transfer_node t;
	ASSERT_EQ(t.get_name(), "undefined");
	LM::My_list<LM::transition_descriptor> lst = t.get_transitions_list();
	LM::My_list<LM::transition_descriptor>::Iterator it = lst.begin();
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info.line_name, "");
		ASSERT_EQ((*it)->info.station_name, "");
	}
}
TEST(Transfer_node_class, inititialize_constructor1) {
	LM::Transfer_node t("new_node");
	ASSERT_EQ(t.get_name(), "new_node");
	LM::My_list<LM::transition_descriptor> lst = t.get_transitions_list();
	LM::My_list<LM::transition_descriptor>::Iterator it = lst.begin();
	int i = 0;
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info.line_name, "");
		ASSERT_EQ((*it)->info.station_name, "");
		i++;
	}
}
TEST(Transfer_node_class, inititialize_constructor2) {
	LM::transition_descriptor mas[3] = { {"red", "r1"},{"blue", "b1"}, {"", ""} };
	LM::Transfer_node t(mas, "new_node");
	ASSERT_EQ(t.get_name(), "new_node");
	LM::My_list<LM::transition_descriptor> lst = t.get_transitions_list();
	LM::My_list<LM::transition_descriptor>::Iterator it = lst.begin();
	int i = 0;
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info.line_name, mas[i].line_name);
		ASSERT_EQ((*it)->info.station_name, mas[i].station_name);
		i++;
	}
}
TEST(Transfer_node_class, get_tranitions_list) {
	LM::transition_descriptor mas[3] = { {"red", "r1"},{"blue", "b1"}, {"black", "b2"} };
	LM::Transfer_node t(mas, "new_node");
	LM::My_list<LM::transition_descriptor> lst = t.get_transitions_list();
	LM::My_list<LM::transition_descriptor>::Iterator it = lst.begin();
	int i = 0;
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info.line_name, mas[i].line_name);
		ASSERT_EQ((*it)->info.station_name, mas[i].station_name);
		i++;
	}
}
TEST(Transfer_node_class, add_transition) {
	LM::transition_descriptor mas[3] = { {"red", "r1"},{"blue", "b1"}, {"", ""} };
	LM::Transfer_node t(mas, "new_node");
	t.add_transition({ "grey","g1" });
	LM::transition_descriptor check_mas[3] = { {"red", "r1"},{"blue", "b1"}, {"grey","g1"} };
	LM::My_list<LM::transition_descriptor> lst = t.get_transitions_list();
	LM::My_list<LM::transition_descriptor>::Iterator it = lst.begin();
	int i = 0;
	for (; it != lst.end(); it++) {
		ASSERT_EQ((*it)->info.line_name, check_mas[i].line_name);
		ASSERT_EQ((*it)->info.station_name, check_mas[i].station_name);
		i++;
	}
}
TEST(Transfer_node_class, add_transition_err1) {
	LM::transition_descriptor mas[3] = { {"red", "r1"},{"blue", "b1"}, {"pink", "p1"} };
	LM::Transfer_node t(mas, "new_node");
	ASSERT_THROW(t.add_transition({ "grey","g1" }), std::out_of_range);
}
TEST(Transfer_node_class, add_transition_err2) {
	LM::transition_descriptor mas[3] = { {"red", "r1"},{"", ""}, {"", ""} };
	LM::Transfer_node t(mas, "new_node");
	ASSERT_THROW(t.add_transition({ "red","r1" }), std::logic_error);
}
TEST(Transfer_node_class, get_type) {
	LM::Transfer_node c;
	ASSERT_EQ(c.get_type(), typeid(LM::Transfer_node).name());
}
TEST(Line_descriptor_class, empty_constructor) {
	LM::Line_descriptor l;
	ASSERT_EQ(l.get_name(), "undefined");
	EXPECT_TRUE(l.is_line_empty());
}
TEST(Line_descriptor_class, initialize_constructor) {
	LM::Line_descriptor l("line1");
	ASSERT_EQ(l.get_name(), "line1");
	EXPECT_TRUE(l.is_line_empty());
}

TEST(Line_descriptor_class, insert) {
	std::string mas[3] = { "red", "green", "" };
	LM::transition_descriptor mas2[3] = { {"red", "r1"},{"blue", "b1"}, {"", ""} };
	LM::Station* st1 = new LM::Station("station1");
	LM::Crossing_station* st2 = new LM::Crossing_station(mas, "station2");
	LM::Transfer_node* st3 = new LM::Transfer_node(mas2, "new_node");

	LM::Line_descriptor line("green");
	line.insert(st1->copy(), line.iter_end());
	line.insert(st2->copy(), line.iter_end());
	line.insert(st3->copy(), line.iter_end());

	LM::My_list<LM::Station*>::Iterator lst_it = line.iter_begin();
	int i = 0;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st1));
	lst_it++;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st2));
	lst_it++;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st3));
}
TEST(Line_descriptor_class, insert_err) {
	LM::Station* mas[5] = { new LM::Station("st1"), new LM::Station("st2"), new LM::Station("st3"), new LM::Station("st4"), new LM::Station("st5") };
	LM::Line_descriptor line("green");
	for (int i = 0; i < 5; i++) {
		line.insert(mas[i]->copy(), line.iter_end());
	}
	LM::Station* st_in = new LM::Station("st2");
	ASSERT_THROW(line.insert(st_in->copy(), line.iter_end()), std::exception);
}
TEST(Line_descriptor_class, get_name) {
	LM::Line_descriptor l("line1");
	ASSERT_EQ(l.get_name(), "line1");
}
TEST(Line_descriptor_class, find) {
	LM::Station* mas[5] = { new LM::Station("st1"), new LM::Station("st2"), new LM::Station("st3"), new LM::Station("st4"), new LM::Station("st5") };
	LM::Line_descriptor line("green");
	for (int i = 0; i < 5; i++) {
		line.insert(mas[i]->copy(), line.iter_end());
	}
	EXPECT_TRUE(comparison(mas[2], line.find("st3")));
}
TEST(Line_descriptor_class, copy_constructor) {
	std::string mas[3] = { "red", "green", "" };
	LM::transition_descriptor mas2[3] = { {"red", "r1"},{"blue", "b1"}, {"", ""} };
	LM::Station* st1 = new LM::Station("station1");
	LM::Crossing_station* st2 = new LM::Crossing_station(mas, "station2");
	LM::Transfer_node* st3 = new LM::Transfer_node(mas2, "new_node");

	LM::Line_descriptor line("green");
	line.insert(st1->copy(), line.iter_end());
	line.insert(st2->copy(), line.iter_end());
	line.insert(st3->copy(), line.iter_end());

	LM::Line_descriptor copy_line(line); //copy constructor

	LM::My_list<LM::Station*>::Iterator lst_it = copy_line.iter_begin();
	int i = 0;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st1));
	lst_it++;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st2));
	lst_it++;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st3));
}
TEST(Line_descriptor_class, copy_assigning) {
	std::string mas[3] = { "red", "green", "" };
	LM::transition_descriptor mas2[3] = { {"red", "r1"},{"blue", "b1"}, {"", ""} };
	LM::Station* st1 = new LM::Station("station1");
	LM::Crossing_station* st2 = new LM::Crossing_station(mas, "station2");
	LM::Transfer_node* st3 = new LM::Transfer_node(mas2, "new_node");

	LM::Line_descriptor line("green");
	line.insert(st1->copy(), line.iter_end());
	line.insert(st2->copy(), line.iter_end());
	line.insert(st3->copy(), line.iter_end());

	LM::Line_descriptor copy_line;
	copy_line = line; //copy assigning

	LM::My_list<LM::Station*>::Iterator lst_it = copy_line.iter_begin();
	int i = 0;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st1));
	lst_it++;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st2));
	lst_it++;
	EXPECT_TRUE(comparison(((*lst_it)->info->copy()), st3));
}
TEST(Line_descriptor_class, remove_station) {
	LM::Station* mas[5] = { new LM::Station("st1"), new LM::Station("st2"), new LM::Station("st3"), new LM::Station("st4"), new LM::Station("st5") };
	LM::Line_descriptor line("green");
	for (int i = 0; i < 5; i++) {
		line.insert(mas[i]->copy(), line.iter_end());
	}
	line.remove_station("st2");
	line.remove_station("st3");
	LM::Station* check_mas[3] = { new LM::Station("st1"), new LM::Station("st4"), new LM::Station("st5") };
	LM::My_list<LM::Station*>::Iterator lst_it = line.iter_begin();
	int i = 0;
	for (; lst_it != line.iter_end(); lst_it++) {
		EXPECT_TRUE(comparison(((*lst_it)->info->copy()), check_mas[i]));
		i++;
	}
}
TEST(Line_descriptor_class, replace_station) {
	LM::Station* mas[3] = { new LM::Station("st1"), new LM::Station("st2"), new LM::Station("st3") };
	LM::Line_descriptor line("green");
	for (int i = 0; i < 3; i++) {
		line.insert(mas[i]->copy(), line.iter_end());
	}
	line.replace_station("st2", new LM::Station("st4"));
	line.replace_station("st3", new LM::Station("st5"));
	LM::Station* check_mas[3] = { new LM::Station("st1"), new LM::Station("st4"), new LM::Station("st5") };
	LM::My_list<LM::Station*>::Iterator lst_it = line.iter_begin();
	int i = 0;
	for (; lst_it != line.iter_end(); lst_it++) {
		EXPECT_TRUE(comparison(((*lst_it)->info->copy()), check_mas[i]));
		i++;
	}
}
TEST(Line_descriptor_class, find_by_transition) {
	std::string mas[3] = { "red", "green", "" };
	LM::transition_descriptor mas2[3] = { {"red", "r1"},{"blue", "b1"}, {"", ""} };
	LM::Station* st1 = new LM::Station("station1");
	LM::Crossing_station* st2 = new LM::Crossing_station(mas, "station2");
	LM::Transfer_node* st3 = new LM::Transfer_node(mas2, "new_node");

	LM::Line_descriptor line("green");
	line.insert(st1->copy(), line.iter_end());
	line.insert(st2->copy(), line.iter_end());
	line.insert(st3->copy(), line.iter_end());

	EXPECT_TRUE(st3->copy(), line.find_by_transition("b1"));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}