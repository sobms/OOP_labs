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
		try // переместить во внешнюю функцию+
		{
			number.Big_decimal::Big_decimal(n);
		}
		catch (std::length_error& error)
		{
			std::cerr << error.what() << std::endl;
			number.Big_decimal::Big_decimal();
			return;
		}
	}
	void Init_from_str(Big_decimal& number) {
		std::cout << "Please enter a string to initialize a number\n";
		char str[47];
		std::cin >> str;
		try // переместить во внешнюю функцию+
		{
			number.Big_decimal::Big_decimal(str);
		}
		catch (std::invalid_argument& error) {
			std::cerr << error.what() << std::endl;
			number.Big_decimal::Big_decimal();
			return;
		}
		catch (std::length_error& error)
		{
			std::cerr << error.what() << std::endl;
			number.Big_decimal::Big_decimal();
			return;
		}
	}
	void Input_number(Big_decimal& number) {
		std::cout << "Please enter in istream your number\n";
		try {
			std::cin >> number;
		}
		catch (std::invalid_argument& err) {
			std::cerr << err.what() << std::endl;
			std::cin.ignore(10000, '\n');  // игнорирует n символов в потоке
			std::cin.clear();             // снимает все флаги с потока
			return;
		}
		if (std::cin.fail()) {
			std::cout << "Input error\n";
			std::cin.ignore(10000, '\n');  // игнорирует n символов в потоке
			std::cin.clear();             // снимает все флаги с потока
		}
	}
	void Get_add_code(Big_decimal& number) {
		std::cout << "Getting additional code...\n";
		Big_decimal code = ~number;
		std::cout << code;
	}
	void Sum_numbers(Big_decimal& number) {
		std::cout << "Please enter the second number\n";
		Big_decimal second;
		char str[47];
		std::cin >> str;
		second = Big_decimal(str);
		std::cout << "Result of sum\n";
		try {
			std::cout << (number + second);
		}
		catch (std::overflow_error& err) {
			std::cerr << err.what() << std::endl;
			return;
		}

		
	}
	void Sub_numbers(Big_decimal& number) {
		std::cout << "Please enter the second number\n";
		Big_decimal second;
		char str[47];
		std::cin >> str;
		second = Big_decimal(str);
		std::cout << "Result of subtraction\n";
		try {
			std::cout << (number - second);
		}
		catch (std::overflow_error& err) {
			std::cerr << err.what() << std::endl;
			return;
		}
	}
	void Mult_by_ten(Big_decimal& number) {
		std::cout << "Result of multiplication\n";
		try
		{
			std::cout << number.Prod_ten();
		}
		catch (std::range_error& err) {
			std::cerr << err.what() << std::endl;
			return;
		}
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
