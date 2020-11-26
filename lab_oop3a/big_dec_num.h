#pragma once
#ifndef _BIG_DEC_NUM_H_
#define _BIG_DEC_NUM_H_

#include <iostream>
namespace lab_oop3 {
	int length(long num);//вынести за пределы класса+
	bool is_number(const char* str);//вынести за пределы класса+

	class Big_dec_num
	{
	private:
		static const int MAX_LEN = 47;
		int len;
		char decimal_num[MAX_LEN] ;
		int Unsigned_Sum(const Big_dec_num& a);//поместить в private+
	public:
		//constructors
		Big_dec_num(); // empty constructor
		Big_dec_num(long num); // initial constructor 1
		Big_dec_num(const char* str); // initial constructor 2
		//setters
		std::istream& Input(std::istream& in); // input
		//getters
		//others
		friend const Big_dec_num Add(const Big_dec_num& a, const Big_dec_num& b); // add number //передавать второй параметр через ссылку+
		friend const Big_dec_num Subtract(const Big_dec_num& a, const Big_dec_num& b); //subtract number
		const Big_dec_num Div_ten() const; //division by ten
		Big_dec_num To_add_code() const; // convert to additional code
		std::ostream& Output(std::ostream& out) const; // output
		const Big_dec_num Prod_ten() const; //increase by ten
	};
}
#endif // !_BIG_DEC_NUM_H_
