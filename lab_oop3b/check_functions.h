#pragma once
#include <iostream>
#include "../library/Big_decimal.h"
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

	void Init_from_long(Big_decimal& number) {
		std::cout << "Please enter a long int to initialize a number\n";
		long n;
		n = get_value();
		number.Big_decimal::Big_decimal(n);
	}
	void Init_from_str(Big_decimal& number) {
		std::cout << "Please enter a string to initialize a number\n";
		char str[47];
		std::cin >> str;
		number.Big_decimal::Big_decimal(str);
	}
	void Input_number(Big_decimal& number) {
		std::cout << "Please enter in istream your number\n";
		std::cin >> number;
		std::cin.ignore(10000, '\n');
	}
	void Get_add_code(Big_decimal& number) {
		std::cout << "Getting additional code...\n";
		Big_decimal code = ~number;
		std::cout << code;
	}
	void Sum_numbers(Big_decimal& number) {///???
		std::cout << "Please enter the second number\n";
		long n;
		Big_decimal second;
		n = get_value();
		second = Big_decimal(n);
		std::cout << "Result of sum\n";
		std::cout << (number + second);
	}
	void Sub_numbers(Big_decimal& number) {///???
		std::cout << "Please enter the second number\n";
		long n;
		Big_decimal second;
		n = get_value();
		second = Big_decimal(n);
		std::cout << "Result of subtraction\n";
		std::cout << (number - second);
	}
	void Mult_by_ten(Big_decimal& number) {
		std::cout << "Result of multiplication\n";
		std::cout << number.Prod_ten();
	}
	void Div_by_ten(Big_decimal& number) {
		std::cout << "Result of division\n";
		std::cout << number.Div_ten();
	}
	void Output_number(Big_decimal& number) {
		std::cout << "Output...\n";
		std::cout << number;
	}
}
