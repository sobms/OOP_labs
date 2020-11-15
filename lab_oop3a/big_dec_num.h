#pragma once
#ifndef _BIG_DEC_NUM_H_
#define _BIG_DEC_NUM_H_

#include <iostream>
namespace lab_oop3 {
	class Big_dec_num
	{
	private:
		static const int MAX_LEN = 47;
		int len;
		char decimal_num[MAX_LEN] ;
	public:
		//constructors
		Big_dec_num(); // empty constructor
		Big_dec_num(long num); // initial constructor 1
		Big_dec_num(const char* str); // initial constructor 2
		//setters
		std::istream& Input(std::istream& in); // input
		//getters
		//others
		const Big_dec_num Add(const Big_dec_num& s) const; // add number
		const Big_dec_num Subtract(const Big_dec_num& s) const; //subtract number
		const Big_dec_num Div_ten() const; //division by ten
		Big_dec_num To_add_code() const; // convert to additional code
		std::ostream& Output(std::ostream& out) const; // output
		const Big_dec_num Prod_ten() const; //increase by ten
		//supportive
		int Unsigned_Sum(const Big_dec_num& a);
		template <class T>
		int length(T num);
		bool is_number(const char* str);
	};
}
#endif // !_BIG_DEC_NUM_H_
