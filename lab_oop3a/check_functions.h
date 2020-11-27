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
		try // переместить во внешнюю функцию+
		{
		number.Big_dec_num::Big_dec_num(n);
		}
		catch (std::length_error& error)
		{
			std::cerr << error.what() << std::endl;
			number.Big_dec_num::Big_dec_num();
			return;
		}
	}
	void Init_from_str(Big_dec_num& number) {
		std::cout << "Please enter a string to initialize a number\n";
		char str[47];
		std::cin >> str;
		try // переместить во внешнюю функцию+
		{
		number.Big_dec_num::Big_dec_num(str);
		}
		catch (std::invalid_argument& error) {
			std::cerr << error.what() << std::endl;
			number.Big_dec_num::Big_dec_num();
			return;
		}
		catch (std::length_error& error)
		{
			std::cerr << error.what() << std::endl;
			number.Big_dec_num::Big_dec_num();
			return;
		}
	}
	void Input_number(Big_dec_num& number) {
		std::cout << "Please enter in istream your number\n";
		try {
			number.Input(std::cin);
		}
		catch (std::invalid_argument& err) {
			std::cerr << err.what() << std::endl;
			number.Big_dec_num::Big_dec_num();
			return;
		}
	}
	void Get_add_code(Big_dec_num& number) {
		std::cout << "Getting additional code...\n";
		Big_dec_num code = number.To_add_code();
		code.Output(std::cout);
	}
	void Sum_numbers(Big_dec_num& number) {
		std::cout << "Please enter the second number\n";
		Big_dec_num second;
		char str[47];
		std::cin >> str;
		second = Big_dec_num(str);
		Big_dec_num result;
		std::cout << "Result of sum\n";
		try {
			number.Add(second, result);
			result.Output(std::cout);
		}
		catch (std::overflow_error& err) {
			std::cerr << err.what() << std::endl;
			return;
		}
	}
	void Sub_numbers(Big_dec_num& number) {///???
		std::cout << "Please enter the second number\n";
		Big_dec_num second;
		char str[47];
		std::cin >> str;
		second = Big_dec_num(str);
		Big_dec_num result;
		std::cout << "Result of subtraction\n";
		try {
			number.Subtract(second, result);
			result.Output(std::cout);
		}
		catch (std::overflow_error& err) {
			std::cerr << err.what() << std::endl;
			return;
		}
	}
	void Mult_by_ten(Big_dec_num& number) {
		std::cout << "Result of multiplication\n";
		try
		{
			number.Prod_ten().Output(std::cout);
		}
		catch (std::range_error& err) {
			std::cerr << err.what() << std::endl;
			return;
		}
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