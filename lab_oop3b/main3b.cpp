#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "../library/Big_decimal.h"
#include "check_functions.h"
using namespace lab_oop3;

int main()
{
	void(*func_ptrs[])(Big_decimal&) = {//по ссылке, чтобы не создавать новый экземпляр
		nullptr,
		Init_from_long,
		Init_from_str,
		Input_number,
		Get_add_code,
		Sum_numbers,
		Sub_numbers,
		Mult_by_ten,
		Div_by_ten,
		Output_number
	};
	const char* options[] =
	{
		"0. Exit\n",
		"1. Enter_new_number_by_first_constructor\n",
		"2. Enter_new_number_by_second_constructor\n",
		"3. Input_number_from_istream\n",
		"4. Get_additional_code\n",
		"5. Sum_of_numbers\n",
		"6. Difference_between_numbers\n",
		"7. Multiply by ten\n",
		"8. Divide by ten\n",
		"9. Output_number\n",
	};
	std::cout << "Enter number of option or '0' to exit from menu\n";
	for (auto elem : options) {
		std::cout << elem;
	}
	char request;
	Big_decimal instance;
	while ((request = _getch()) != '0') {
		request -= '0';
		if ((request > 0) && (request <= 9)) {
			system("cls");
			func_ptrs[request](instance);
			_getch();
			system("cls");
		}
		else {
			system("cls");
			std::cout << "Option with such number does not exist. Please, enter correct number of option!\n";
			std::cout << "press any key to continue\n";
			_getch();
			system("cls");
		}
		std::cout << "Enter number of option or '0' to exit from menu\n";
		for (auto elem : options) {
			std::cout << elem;
		}
	}

	return 0;
}
