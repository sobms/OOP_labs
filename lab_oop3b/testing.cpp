#include <iostream>
#include "../library/Big_decimal.h"
#include "gtest/gtest.h"
namespace l3 = lab_oop3;

TEST(DecimalConstructors, EmptyConstructor) {
	l3::Big_decimal num1;
	ASSERT_EQ(num1.Get_len(), 1);
	EXPECT_TRUE(num1.compare_numbers("000000000000000000000000000"));
}
TEST(DecimalConstructors, InitLongConstructor) {
	l3::Big_decimal num1(324524);
	ASSERT_EQ(num1.Get_len(), 6);
	EXPECT_TRUE(num1.compare_numbers("042542300000000000000000000"));
	l3::Big_decimal num2(-9245274);
	ASSERT_EQ(num2.Get_len(), 7);
	EXPECT_TRUE(num2.compare_numbers("147254290000000000000000000"));
}
TEST(DecimalConstructors, InitStrConstructor) {
	l3::Big_decimal num1("98774557643");
	ASSERT_EQ(num1.Get_len(), 11);
	EXPECT_TRUE(num1.compare_numbers("034675547789000000000000000"));
	l3::Big_decimal num2("-557643");
	ASSERT_EQ(num2.Get_len(), 6);
	EXPECT_TRUE(num2.compare_numbers("134675500000000000000000000"));
	l3::Big_decimal num3("-0000557643");
	ASSERT_EQ(num3.Get_len(), 6);
	EXPECT_TRUE(num3.compare_numbers("134675500000000000000000000"));
	ASSERT_THROW(l3::Big_decimal num5("--64435"), std::invalid_argument);
	ASSERT_THROW(l3::Big_decimal num6("98764664244654345365345345345386756"), std::length_error);
	l3::Big_decimal num7("");
	ASSERT_EQ(num7.Get_len(), 1);
	EXPECT_TRUE(num7.compare_numbers("000000000000000000000000000"));
	l3::Big_decimal num8("-0");
	ASSERT_EQ(num8.Get_len(), 1);
	EXPECT_TRUE(num8.compare_numbers("000000000000000000000000000"));

}
TEST(DecimalNumberOperators, AddCode) {
	l3::Big_decimal num1("98653");
	EXPECT_TRUE(~num1.compare_numbers("035689000000000000000000000"));
	l3::Big_decimal num2("-9865356");
	EXPECT_TRUE(~num2.compare_numbers("144643109999999999999999999"));
}
TEST(DecimalNumberOperators, Add) {
	l3::Big_decimal first("345278");
	l3::Big_decimal second("-812646");
	l3::Big_decimal res = (first + second);
	EXPECT_TRUE(res.compare_numbers("186376400000000000000000000"));
	l3::Big_decimal second2("654722");
	ASSERT_THROW((first + second2), std::overflow_error);
	l3::Big_decimal first3("345278000");
	l3::Big_decimal second3("812646");
	res = (first3 + second3);
	EXPECT_TRUE(res.compare_numbers("064609064300000000000000000"));
}
TEST(DecimalNumberOperators, Subtract) {
	l3::Big_decimal first("87956");
	l3::Big_decimal second("89264");
	l3::Big_decimal result = (first - second);
	EXPECT_TRUE(result.compare_numbers("180310000000000000000000000"));
}
TEST(OtherMethods, ProdTen) {
	l3::Big_decimal num1("21064");
	l3::Big_decimal res = num1.Prod_ten();
	EXPECT_TRUE(res.compare_numbers("004601200000000000000000000"));
	l3::Big_decimal num2("56745678921349087675765271");
	ASSERT_THROW(num2.Prod_ten(), std::range_error);
	l3::Big_decimal num3("-87123");
	res = num3.Prod_ten();
	EXPECT_TRUE(res.compare_numbers("103217800000000000000000000"));
	l3::Big_decimal num4("0");
	res = num4.Prod_ten();
	EXPECT_TRUE(res.compare_numbers("000000000000000000000000000"));
}
TEST(OtherMethods, DivTen) {
	l3::Big_decimal num1("-98654");
	l3::Big_decimal res = num1.Div_ten();
	EXPECT_TRUE(res.compare_numbers("156890000000000000000000000"));
	l3::Big_decimal num2("0");
	res = num2.Div_ten();
	EXPECT_TRUE(res.compare_numbers("000000000000000000000000000"));

}
int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}