#pragma once
#ifndef _Big_decimal_H_
#define _Big_decimal_H_

#include <iostream>
namespace lab_oop3 {
	class Big_decimal
	{
	private:
		int max_len;
		int len;
		char *decimal_num;
	public:
		//constructors
		Big_decimal(); // empty constructor
		Big_decimal(long num); // initial constructor 1
		Big_decimal(std::string str); // initial constructor 2
		Big_decimal(const Big_decimal& sample); //copying construstor
		~Big_decimal() { delete[] decimal_num; decimal_num = nullptr; }; //destructor
		Big_decimal& operator =(const Big_decimal& a); //assigning
		friend std::istream& operator >> (std::istream& in, Big_decimal& a); // input
		const Big_decimal operator + (const Big_decimal& a) const; // add number
		const Big_decimal operator - (const Big_decimal& a) const; //subtract number
		const Big_decimal Div_ten() const; //division by ten
		Big_decimal operator ~() const; // convert to additional code
		friend std::ostream& operator << (std::ostream& out, const Big_decimal& a); // output
		const Big_decimal Prod_ten() const; //increase by ten
		//supportive
		int Unsigned_Sum(const Big_decimal& a);
		template <class T>
		int length(T num);
		bool is_number(std::string str);
	};
}
#endif // !_Big_decimal_H_