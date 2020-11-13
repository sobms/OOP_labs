#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "../lab_oop3_lib/big_dec_num.h"
#include "check_functions.h"
using namespace lab_oop3;

int main()
{
	void(*func_ptrs[])(Big_dec_num&) = {//по ссылке, чтобы не создавать новый экземпляр
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
	for (int i = 0; i < (sizeof(options) / sizeof(options[0])); i++) {
		std::cout << options[i];
	}
	char request;
	Big_dec_num instance;
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
			std::cout<<"Option with such number does not exist. Please, enter correct number of option!\n";
			std::cout << "press any key to continue\n";
			_getch();
			system("cls");
		}
		std::cout << "Enter number of option or '0' to exit from menu\n";
		for (int i = 0; i < (sizeof(options) / sizeof(options[0])); i++) {
			std::cout << options[i];
		}
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
