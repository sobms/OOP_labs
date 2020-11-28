#pragma once
#ifndef _Big_decimal_H_
#define _Big_decimal_H_

#include <iostream>
namespace lab_oop3 {

	int length(long num);
	bool is_number(std::string& str);
	bool check_str(std::string& str);
	

	class Big_decimal
	{
	private:
		int max_len;
		int len;
		char *decimal_num;
		//supportive
		int Unsigned_Sum(const Big_decimal& a);
		Big_decimal& Get_mem(int size); // new+
	public:
		//constructors
		Big_decimal(); // empty constructor
		Big_decimal(long num); // initial constructor 1
		Big_decimal(std::string& str); // initial constructor 2          //string&+(ссылка не константная, т к в строке нужно удалять пробелы)
		Big_decimal(const Big_decimal& sample); //copying construstor
		Big_decimal(Big_decimal&& sample) : max_len(sample.max_len), len(sample.len), decimal_num(sample.decimal_num) {
			sample.decimal_num = nullptr;
		}										//moving constructor+

		~Big_decimal() { delete[] decimal_num;}; //destructor
		Big_decimal& operator = (const Big_decimal& a); //assigning
		Big_decimal& operator = (Big_decimal&& a);		//moving+
		friend std::istream& operator >> (std::istream& in, Big_decimal& a); // input
		friend const Big_decimal operator + (const Big_decimal& a, const Big_decimal& b); // add number
		friend const Big_decimal operator - (const Big_decimal& a, const Big_decimal& b); //subtract number
		void Div_ten(Big_decimal& res) const; //division by ten
		Big_decimal operator ~() const; // convert to additional code
		friend std::ostream& operator << (std::ostream& out, const Big_decimal& a); // output
		void Prod_ten(Big_decimal& res) const; //increase by ten
	}; 
}
//исправлен delete[]+
//применены изменения из предыдущих лаб+
// перемещающий конструктор и перемещающее присваивание+
#endif // !_Big_decimal_H_