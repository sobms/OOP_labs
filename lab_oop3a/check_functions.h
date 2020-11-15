#include <iostream>
#include "../lab_oop3_lib/big_dec_num.h"
#pragma once
namespace lab_oop3 {
	long get_value() {
		while (true)
		{
			long a;
			std::cin >> a;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "Oops, that input is invalid. Please try again.\n";
			}
			else
			{
				std::cin.ignore(32767, '\n');
				return a;
			}
		}
	}

	void Init_from_long(Big_dec_num &number) {
		std::cout << "Please enter a long int to initialize a number\n";
		long n;
		n = get_value();
		number.Big_dec_num::Big_dec_num(n);
	}
	void Init_from_str(Big_dec_num& number) {
		std::cout << "Please enter a string to initialize a number\n";
		char str[47];
		std::cin >> str;
		//std::cin.clear();
		number.Big_dec_num::Big_dec_num(str);
	}
	void Input_number(Big_dec_num& number) {
		std::cout << "Please enter in istream your number\n";
		number.Input(std::cin);		
		//std::cin.clear();
	}
	void Get_add_code(Big_dec_num& number) {
		std::cout << "Getting additional code...\n";
		Big_dec_num code = number.To_add_code();
		code.Output(std::cout);
	}
	void Sum_numbers(Big_dec_num& number) {///???
		std::cout << "Please enter the second number\n";
		long n;
		Big_dec_num second;
		n = get_value();
		second = Big_dec_num(n);
		std::cout << "Result of sum\n";
		number.Add(second).Output(std::cout);
	}
	void Sub_numbers(Big_dec_num& number) {///???
		std::cout << "Please enter the second number\n";
		long n;
		Big_dec_num second;
		n = get_value();
		second = Big_dec_num(n);
		std::cout << "Result of subtraction\n";
		number.Subtract(second).Output(std::cout);
	}
	void Mult_by_ten(Big_dec_num& number) {
		std::cout << "Result of multiplication\n";
		number.Prod_ten().Output(std::cout);
	}
	void Div_by_ten(Big_dec_num& number) {
		std::cout << "Result of division\n";
		number.Div_ten().Output(std::cout);
	}
	void Output_number(Big_dec_num& number) {
		std::cout << "Output...\n";
		number.Output(std::cout);
	}
}