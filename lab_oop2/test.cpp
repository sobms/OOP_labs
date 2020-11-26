//#include "pch.h"
#include "../library/Epicicloid.h"
#include "gtest/gtest.h"
#pragma warning(disable : 4996)

namespace epc = epicicloid1;
TEST(EpicicloidConstrucor, EmptyConstructor) {
	epc:: Epicicloid e1;
	double approx_val = 0.00001;
	ASSERT_NEAR(1.0, e1.get_r(), approx_val);     // assert near для вещественных значений+
	ASSERT_NEAR(1.0, e1.get_R(), approx_val);
	ASSERT_NEAR(1.0, e1.get_d(), approx_val);
	ASSERT_NEAR(0.0, e1.get_p().x, approx_val);
	ASSERT_NEAR(0.0, e1.get_p().y, approx_val);
}
TEST(EpicicloidConstructor, InitConstructor) {
	epc::point p (-1, 2);
	double approx_val = 0.00001;
	epc::Epicicloid e1(p, 3, 15, 5);
	ASSERT_NEAR(-1.0, e1.get_p().x, approx_val);
	ASSERT_NEAR(2.0, e1.get_p().y, approx_val);
	ASSERT_NEAR(3.0, e1.get_r(), approx_val);
	ASSERT_NEAR(15.0, e1.get_R(), approx_val);
	ASSERT_NEAR(5.0, e1.get_d(), approx_val);
}
TEST(EpicicloidConstructor, InitConstructor2) {
	epc::Epicicloid e1(-3,-4, 3, 15, 5);
	double approx_val = 0.00001;
	ASSERT_NEAR(-3.0, e1.get_p().x, approx_val);
	ASSERT_NEAR(-4.0, e1.get_p().y, approx_val);
	ASSERT_NEAR(3.0, e1.get_r(), approx_val);
	ASSERT_NEAR(15.0, e1.get_R(), approx_val);
	ASSERT_NEAR(5.0, e1.get_d(), approx_val);
}
TEST(EpicicloidConstructor, Exception) {
	
	ASSERT_THROW(epc::Epicicloid e1(0, 0, 4, -5, 4), std::invalid_argument); // проверить ожидаемый тип исключения 
	ASSERT_THROW(epc::Epicicloid e1(0, 0, -16, 10, -5), std::length_error);
	ASSERT_THROW(epc::Epicicloid e1(0, 0, 4, 12, -20), std::length_error);
}
TEST(EpicicloidMethods, Setters) {
	epc::Epicicloid a;
	double approx_val = 0.00001;
	a.set_r(6);
	ASSERT_NEAR(6.0, a.get_r(), approx_val);// проверить что другие значения не изменились+
	ASSERT_NEAR(1.0, a.get_R(), approx_val);
	ASSERT_NEAR(1.0, a.get_d(), approx_val);
	ASSERT_NEAR(0.0, a.get_p().x, approx_val);
	ASSERT_NEAR(0.0, a.get_p().y, approx_val);

	a.set_R(5);
	ASSERT_NEAR(6.0, a.get_r(), approx_val);
	ASSERT_NEAR(5.0, a.get_R(), approx_val);
	ASSERT_NEAR(1.0, a.get_d(), approx_val);
	ASSERT_NEAR(0.0, a.get_p().x, approx_val);
	ASSERT_NEAR(0.0, a.get_p().y, approx_val);

	a.set_d(4);
	ASSERT_NEAR(6.0, a.get_r(), approx_val);
	ASSERT_NEAR(5.0, a.get_R(), approx_val);
	ASSERT_NEAR(4.0, a.get_d(), approx_val);
	ASSERT_NEAR(0.0, a.get_p().x, approx_val);
	ASSERT_NEAR(0.0, a.get_p().y, approx_val);

	a.set_point({ 8.0, 8.0 });
	ASSERT_NEAR(6.0, a.get_r(), approx_val);
	ASSERT_NEAR(5.0, a.get_R(), approx_val);
	ASSERT_NEAR(4.0, a.get_d(), approx_val);
	ASSERT_NEAR(8.0, a.get_p().x, approx_val);
	ASSERT_NEAR(8.0, a.get_p().y, approx_val);

	ASSERT_THROW(a.set_r(-6), std::length_error);
	ASSERT_THROW(a.set_d(-7), std::length_error);
	ASSERT_THROW(a.set_R(-1), std::invalid_argument);
}
TEST(EpicicloidMethods, Selectors) { // дополнительные тесты с другими значениями+
	epc::Epicicloid a(0, 0, 2, 5, 3);
	double error = (0.05);
	ASSERT_NEAR(a.get_coordinates(60).x, 6.098, error);
	ASSERT_NEAR(a.get_coordinates(60).y, 7.562178, error);
	ASSERT_EQ(10, a.get_border_rads().R);
	ASSERT_EQ(4, a.get_border_rads().r);
	ASSERT_EQ(false, a.Is_astroid());
	ASSERT_EQ(2, a.get_type());
	ASSERT_NEAR(a.sect_area(60), 32.7, error);
	ASSERT_NEAR(a.get_curv_rad(60), 6.72, 0.01);
}

TEST(EpicicloidMethods2, Selectors) {
	epc::Epicicloid a(4, 2, -2, 8, -2);
	double error = (0.05);
	ASSERT_NEAR(a.get_coordinates(30).y, 3.0, error);
	ASSERT_NEAR(a.get_coordinates(30).x, 9.19615, error);
	ASSERT_EQ(true, a.Is_astroid());
	ASSERT_EQ(3, a.get_type());
	ASSERT_NEAR(a.sect_area(30), 3.6851, error);
	ASSERT_NEAR(a.get_curv_rad(30), 10.3923, 0.01);
}





int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}