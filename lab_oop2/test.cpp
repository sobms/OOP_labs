//#include "pch.h"
#include "../library/Epicicloid.h"
#include "gtest/gtest.h"
#pragma warning(disable : 4996)

namespace epc = epicicloid1;
TEST(EpicicloidConstrucor, EmptyConstructor) {
	epc:: Epicicloid e1;
	ASSERT_EQ(1.0, e1.get_r());
	ASSERT_EQ(1.0, e1.get_R());
	ASSERT_EQ(1.0, e1.get_d());
	ASSERT_EQ(0.0, e1.get_p().x);
	ASSERT_EQ(0.0, e1.get_p().y);
}
TEST(EpicicloidConstructor, InitConstructor) {
	epc::point p (-1, 2);
	epc::Epicicloid e1(p, 3, 15, 5);
	ASSERT_EQ(-1.0, e1.get_p().x);
	ASSERT_EQ(2.0, e1.get_p().y);
	ASSERT_EQ(3.0, e1.get_r());
	ASSERT_EQ(15.0, e1.get_R());
	ASSERT_EQ(5.0, e1.get_d());
}
TEST(EpicicloidConstructor, InitConstructor2) {
	epc::Epicicloid e1(-3,-4, 3, 15, 5);
	ASSERT_EQ(-3.0, e1.get_p().x);
	ASSERT_EQ(-4.0, e1.get_p().y);
	ASSERT_EQ(3.0, e1.get_r());
	ASSERT_EQ(15.0, e1.get_R());
	ASSERT_EQ(5.0, e1.get_d());
}
TEST(EpicicloidConstructor, Exception) {
	
	ASSERT_ANY_THROW(epc::Epicicloid e1(0, 0, 4, -5, 4));
	ASSERT_ANY_THROW(epc::Epicicloid e1(0, 0, -16, 10, -5));
	ASSERT_ANY_THROW(epc::Epicicloid e1(0, 0, 4, 12, -20));
}
TEST(EpicicloidMethods, Setters) {
	epc::Epicicloid a;
	a.set_r(6);
	ASSERT_EQ(6, a.get_r());
	a.set_R(5);
	ASSERT_EQ(5, a.get_R());
	a.set_d(4);
	ASSERT_EQ(4, a.get_d());
	a.set_point({ 8.0, 8.0 });
	ASSERT_EQ(8, a.get_p().x);
	ASSERT_EQ(8, a.get_p().y);
	ASSERT_ANY_THROW(a.set_r(-6));
	ASSERT_ANY_THROW(a.set_d(-7));
	ASSERT_ANY_THROW(a.set_R(-1));
}
TEST(EpicicloidMethods, Selectors) {
	epc::Epicicloid a(0, 0, 2, 5, 3); 
	double error = (0.05);
	ASSERT_NEAR(a.get_coordinates(60).x, -4.015, error);
	ASSERT_NEAR(a.get_coordinates(60).y, -3.537, error);
	ASSERT_EQ(10, a.get_border_rads().R);
	ASSERT_EQ(4, a.get_border_rads().r);
	ASSERT_EQ(false, a.Is_astroid());
	ASSERT_EQ("extended\0", a.get_type());
	ASSERT_NEAR(a.sect_area(60), 32.7, error);
	ASSERT_NEAR(a.get_curv_rad(60), 6.72, 0.01);
}





int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}