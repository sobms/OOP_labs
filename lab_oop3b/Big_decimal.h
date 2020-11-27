#pragma once
#ifndef _Big_decimal_H_
#define _Big_decimal_H_

#include <iostream>
namespace lab_oop3 {
	int length(long num);
	bool is_number(const char* str);
	bool check_str(const char* str);

	class Big_decimal
	{
	private:
		static const int MAX_LEN = 47;
		int len;
		char decimal_num[MAX_LEN];
		int Unsigned_Sum(const Big_decimal& a);
	public:
		//constructors
		Big_decimal(); // empty constructor
		Big_decimal(long num); // initial constructor 1
		Big_decimal(const char* str); // initial constructor 2
		//setters
		friend std::istream& operator >> (std::istream& in, Big_decimal& a); // input //remade+
		//getters
		//others
		friend const Big_decimal operator + (const Big_decimal& a, const Big_decimal& b); // add number
		friend const Big_decimal operator - (const Big_decimal& a, const Big_decimal& b); //subtract number
		const Big_decimal Div_ten() const; //division by ten
		Big_decimal operator ~() const; // convert to additional code
		friend std::ostream& operator << (std::ostream& out, const Big_decimal& a); // output
		const Big_decimal Prod_ten() const; //increase by ten
	};
}//changes moved from lab 3a+
#endif // !_Big_decimal_H_