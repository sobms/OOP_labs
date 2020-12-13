#include <iostream>
#include "../lab_oop3_lib/big_dec_num.h"
#include "gtest/gtest.h"
#include <conio.h>
namespace l3 = lab_oop3;

TEST(DecimalConstructors, EmptyConstructor) {
	l3::Big_dec_num num1;
	ASSERT_EQ(num1.Get_len(), 1);
	EXPECT_TRUE(num1.compare_numbers("000000000000000000000000000"));
}
TEST(DecimalConstructors, InitLongConstructor) {
	l3::Big_dec_num num1(324524);
	ASSERT_EQ(num1.Get_len(), 6);
	EXPECT_TRUE(num1.compare_numbers("042542300000000000000000000"));
	l3::Big_dec_num num2(-9245274);
	ASSERT_EQ(num2.Get_len(), 7);
	EXPECT_TRUE(num2.compare_numbers("147254290000000000000000000"));
}
TEST(DecimalConstructors, InitStrConstructor) {
	l3::Big_dec_num num1("98774557643");
	ASSERT_EQ(num1.Get_len(), 11);
	EXPECT_TRUE(num1.compare_numbers("034675547789000000000000000"));
	l3::Big_dec_num num2("-557643");
	ASSERT_EQ(num2.Get_len(), 6);
	EXPECT_TRUE(num2.compare_numbers("134675500000000000000000000"));
	l3::Big_dec_num num3("-0000557643");
	ASSERT_EQ(num3.Get_len(), 6);
	EXPECT_TRUE(num3.compare_numbers("134675500000000000000000000"));
	l3::Big_dec_num num4("0000-0000123456789");
	ASSERT_EQ(num4.Get_len(), 9);
	EXPECT_TRUE(num4.compare_numbers("198765432100000000000000000"));
	ASSERT_THROW(l3::Big_dec_num num5("--64435"), std::invalid_argument);
	ASSERT_THROW(l3::Big_dec_num num6("98764664244654345365345345345386756"), std::length_error);
	l3::Big_dec_num num7("");
	ASSERT_EQ(num7.Get_len(), 1);
	EXPECT_TRUE(num7.compare_numbers("000000000000000000000000000"));
	l3::Big_dec_num num8("-0");
	ASSERT_EQ(num8.Get_len(), 1);
	EXPECT_TRUE(num8.compare_numbers("000000000000000000000000000"));

}
TEST(OtherMethods, AddCode) {
	l3::Big_dec_num num1("98653");
	EXPECT_TRUE(num1.To_add_code().compare_numbers("035689000000000000000000000"));
	l3::Big_dec_num num2("-9865356");
	EXPECT_TRUE(num2.To_add_code().compare_numbers("144643109999999999999999999"));
}
TEST(OtherMethods, Add) {
	l3::Big_dec_num first("345278");
	l3::Big_dec_num second("-812646");
	l3::Big_dec_num result;
	first.Add(second, result);
	EXPECT_TRUE(result.compare_numbers("186376400000000000000000000"));
	l3::Big_dec_num second2("654722");
	ASSERT_THROW(first.Add(second2, result), std::overflow_error);
	l3::Big_dec_num first3("345278000");
	l3::Big_dec_num second3("812646");
	first3.Add(second3, result);
	EXPECT_TRUE(result.compare_numbers("064609064300000000000000000"));
}
TEST(OtherMethods, Subtract) {
	l3::Big_dec_num first("87956");
	l3::Big_dec_num second("89264");
	l3::Big_dec_num result;
	first.Subtract(second, result);
	EXPECT_TRUE(result.compare_numbers("180310000000000000000000000"));
}
TEST(OtherMethods, ProdTen) {
	l3::Big_dec_num num1("21064");
	l3::Big_dec_num res = num1.Prod_ten();
	EXPECT_TRUE(res.compare_numbers("004601200000000000000000000"));
	l3::Big_dec_num num2("56745678921349087675765271");
	ASSERT_THROW(num2.Prod_ten(), std::range_error);
	l3::Big_dec_num num3("-87123");
	res = num3.Prod_ten();
	EXPECT_TRUE(res.compare_numbers("103217800000000000000000000"));
	l3::Big_dec_num num4("0");
	res = num4.Prod_ten();
	EXPECT_TRUE(res.compare_numbers("000000000000000000000000000"));
}
TEST(OtherMethods, DivTen) {
	l3::Big_dec_num num1("-98654");
	l3::Big_dec_num res = num1.Div_ten();
	EXPECT_TRUE(res.compare_numbers("156890000000000000000000000"));
	l3::Big_dec_num num2("0");
	res = num2.Div_ten();
	EXPECT_TRUE(res.compare_numbers("000000000000000000000000000"));

}
int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}