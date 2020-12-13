#include <iostream>
#include "../library_3c/Big_decimal.h"
#include "gtest/gtest.h"
#include <string.h>
#include <string>
namespace l3 = lab_oop3;

TEST(DecimalConstructors, EmptyConstructor) {
	l3::Big_decimal num1;
	ASSERT_EQ(num1.Get_len(), 1);
	ASSERT_EQ(num1.Get_max_len(), 27);
	EXPECT_TRUE(num1.compare_numbers("000000000000000000000000000"));
}
TEST(DecimalConstructors, InitLongConstructor) {
	l3::Big_decimal num1(324524);
	ASSERT_EQ(num1.Get_len(), 6);
	ASSERT_EQ(num1.Get_max_len(), 27);
	EXPECT_TRUE(num1.compare_numbers("042542300000000000000000000"));
	l3::Big_decimal num2(-9245274);
	ASSERT_EQ(num2.Get_len(), 7);
	ASSERT_EQ(num2.Get_max_len(), 27);
	EXPECT_TRUE(num2.compare_numbers("147254290000000000000000000"));
}
TEST(DecimalConstructors, InitStrConstructor) {
	std::string str1 = "98774557643";
	l3::Big_decimal num1(str1);
	ASSERT_EQ(num1.Get_len(), 11);
	ASSERT_EQ(num1.Get_max_len(), 27);
	EXPECT_TRUE(num1.compare_numbers("034675547789000000000000000"));
	str1 = "-557643";
	l3::Big_decimal num2(str1);
	ASSERT_EQ(num2.Get_len(), 6);
	ASSERT_EQ(num2.Get_max_len(), 27);
	EXPECT_TRUE(num2.compare_numbers("134675500000000000000000000"));
	str1 = "-0000557643";
	l3::Big_decimal num3(str1);
	ASSERT_EQ(num3.Get_len(), 6);
	ASSERT_EQ(num3.Get_max_len(), 27);
	EXPECT_TRUE(num3.compare_numbers("134675500000000000000000000"));
	str1 = "00000-0000557643";
	l3::Big_decimal num4(str1);
	ASSERT_EQ(num4.Get_max_len(), 27);
	ASSERT_EQ(num4.Get_len(), 6);
	EXPECT_TRUE(num4.compare_numbers("134675500000000000000000000"));

	str1 = "--64435";
	ASSERT_THROW(l3::Big_decimal num5(str1), std::invalid_argument);
	str1 = "1111122222333334444455555666667777788888";
	l3::Big_decimal num6(str1);
	ASSERT_EQ(num6.Get_len(), 40);
	ASSERT_EQ(num6.Get_max_len(), 54);
	EXPECT_TRUE(num6.compare_numbers("088888777776666655555444443333322222111110000000000000"));
	str1 = "";
	l3::Big_decimal num7(str1);
	ASSERT_EQ(num7.Get_len(), 1);
	ASSERT_EQ(num7.Get_max_len(), 27);
	EXPECT_TRUE(num7.compare_numbers("000000000000000000000000000"));
	str1 = "-0";
	l3::Big_decimal num8(str1);
	ASSERT_EQ(num8.Get_len(), 1);
	ASSERT_EQ(num8.Get_max_len(), 27);
	EXPECT_TRUE(num8.compare_numbers("000000000000000000000000000"));
}
TEST(DecimalConstructors, CopyConstructor) {
	l3::Big_decimal num1(-765487);
	l3::Big_decimal num2(num1);
	ASSERT_EQ(num2.Get_len(), 6);
	ASSERT_EQ(num2.Get_max_len(), 27);
	EXPECT_TRUE(num2.compare_numbers("178456700000000000000000000"));
}
TEST(DecimalNumberOperators, Assigning) {
	std::string str = "1111122222333334444455555666667777788888";
	l3::Big_decimal num(str);
	l3::Big_decimal res;
	res = num;
	ASSERT_EQ(res.Get_len(), 40);
	ASSERT_EQ(res.Get_max_len(), 54);
	EXPECT_TRUE(res.compare_numbers("088888777776666655555444443333322222111110000000000000"));
}
TEST(DecimalNumberOperators, AddCode) {
	l3::Big_decimal num1(98653);
	EXPECT_TRUE(~num1.compare_numbers("035689000000000000000000000"));
	l3::Big_decimal num2(-9865356);
	EXPECT_TRUE(~num2.compare_numbers("144643109999999999999999999"));
}
TEST(DecimalNumberOperators, Add) {
	l3::Big_decimal first(345278);
	l3::Big_decimal second(-812646);
	l3::Big_decimal res = (first + second);
	ASSERT_EQ(res.Get_len(), 6);
	ASSERT_EQ(res.Get_max_len(), 27);
	EXPECT_TRUE(res.compare_numbers("186376400000000000000000000"));
	l3::Big_decimal second2(654722);
	res = first + second2;
	EXPECT_TRUE(res.compare_numbers("000000010000000000000000000"));
	ASSERT_EQ(res.Get_len(), 7);
	ASSERT_EQ(res.Get_max_len(), 27);
	l3::Big_decimal first3(3452780);
	l3::Big_decimal second3(812646);
	res = (first3 + second3);
	EXPECT_TRUE(res.compare_numbers("062456240000000000000000000"));
	ASSERT_EQ(res.Get_len(), 7);
	ASSERT_EQ(res.Get_max_len(), 27);
	std::string str1 = "12345678912345678912345678";
	std::string str2 = "98765432198765432198765432";
	l3::Big_decimal first4(str1);
	l3::Big_decimal second4(str2);
	res = (first4 + second4);
	EXPECT_TRUE(res.compare_numbers("001111111111111111111111111100000000000000000000000000"));
	ASSERT_EQ(res.Get_len(), 27);     
	ASSERT_EQ(res.Get_max_len(), 54);
	str1 = "-12345678912345678912345678";
	str2 = "98765432198765432198765432";
	l3::Big_decimal first5(str1);
	l3::Big_decimal second5(str2);
	res = (first5 + second5);
	EXPECT_TRUE(res.compare_numbers("045791468235791468235791468"));
	ASSERT_EQ(res.Get_len(), 26);
	ASSERT_EQ(res.Get_max_len(), 27);
}
TEST(DecimalNumberOperators, Subtract) {
	l3::Big_decimal first(87956);
	l3::Big_decimal second(89264);
	l3::Big_decimal result = (first - second);
	EXPECT_TRUE(result.compare_numbers("180310000000000000000000000"));
	ASSERT_EQ(result.Get_len(), 4); 
	ASSERT_EQ(result.Get_max_len(), 27);
	std::string str1 = "-12345678912345678912345678";
	std::string str2 = "98765432198765432198765432";
	l3::Big_decimal first1(str1);
	l3::Big_decimal second1(str2);
	l3::Big_decimal res = (first1 - second1);
	EXPECT_TRUE(res.compare_numbers("101111111111111111111111111100000000000000000000000000"));
	ASSERT_EQ(res.Get_len(), 27);
	ASSERT_EQ(res.Get_max_len(), 54);
	str1 = "12345678912345678912345678";
	str2 = "98765432198765432198765432";
	l3::Big_decimal first2(str1);
	l3::Big_decimal second2(str2);
	res = (first2 - second2);
	EXPECT_TRUE(res.compare_numbers("145791468235791468235791468"));
	ASSERT_EQ(res.Get_len(), 26);
	ASSERT_EQ(res.Get_max_len(), 27);
}
TEST(OtherMethods, ProdTen) {
	l3::Big_decimal num1(21064);
	l3::Big_decimal res(num1);
	num1.Prod_ten(res);
	EXPECT_TRUE(res.compare_numbers("004601200000000000000000000"));
	ASSERT_EQ(res.Get_len(), 6);
	ASSERT_EQ(res.Get_max_len(), 27);
	l3::Big_decimal num2(-87123);
	l3::Big_decimal res2(num2);
	num2.Prod_ten(res2);
	EXPECT_TRUE(res2.compare_numbers("103217800000000000000000000"));
	ASSERT_EQ(res2.Get_len(), 6);
	ASSERT_EQ(res.Get_max_len(), 27);
	l3::Big_decimal num3(0);
	l3::Big_decimal res3(num3);
	num3.Prod_ten(res3);
	EXPECT_TRUE(res3.compare_numbers("000000000000000000000000000"));
	ASSERT_EQ(res3.Get_len(), 1);
	ASSERT_EQ(res.Get_max_len(), 27);
	std::string str1 = "12345678912345678912345678";
	l3::Big_decimal num4(str1);
	l3::Big_decimal res4(num4);
	num4.Prod_ten(res4);
	EXPECT_TRUE(res4.compare_numbers("008765432198765432198765432100000000000000000000000000"));
	ASSERT_EQ(res4.Get_len(), 27);
	ASSERT_EQ(res4.Get_max_len(), 54);
}
TEST(OtherMethods, DivTen) {
	l3::Big_decimal num1(21064);
	l3::Big_decimal res(num1);
	num1.Div_ten(res);
	EXPECT_TRUE(res.compare_numbers("060120000000000000000000000"));
	ASSERT_EQ(res.Get_len(), 4);
	ASSERT_EQ(res.Get_max_len(), 27);
	l3::Big_decimal num3(0);
	l3::Big_decimal res3(num3);
	num3.Div_ten(res3);
	EXPECT_TRUE(res3.compare_numbers("000000000000000000000000000"));
	ASSERT_EQ(res3.Get_len(), 1);
	ASSERT_EQ(res.Get_max_len(), 27);
	std::string str1 = "123456789123456789123456785";
	l3::Big_decimal num4(str1);
	l3::Big_decimal res4(num4);
	num4.Div_ten(res4);
	EXPECT_TRUE(res4.compare_numbers("087654321987654321987654321"));
	ASSERT_EQ(res4.Get_len(), 26);
	ASSERT_EQ(res4.Get_max_len(), 27);
}
int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}