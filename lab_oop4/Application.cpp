#include <iostream>
#include "../Station_discriptors/Station_discriptors.h"
#include "../Metro_line/Line_descriptor.h"
#include "Dialog_functions.h"
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace Metro_line;

std::string menu[] = {
   "1. Add new station in line",
   "2. Remove station",
   "3. Modify station",
   "4. Find station in line by name",
   "5. Find station in line by name of tansfer station",
   "6. Show_line",
   "7. Quit"
};
void (*f_ptrs[])(Line_descriptor&) = {
    nullptr,
    Add,
    Remove,
    Change,
    Find,
    Find_by_name_transfer_station,
    Show_line
};
int Get_answer() {
    int choice=0;
    do {
        // отрисовка меню
        system("cls");
        for (auto i : menu) {
            std::cout << i << std::endl;
        }
        std::cout << "Press 1-7 to choose option" << std::endl;
        // выбор пользователя
        std::cin>>choice;
        
        if (!std::cin.good()) {
            std::cout << "Input error! Press any key and try again..." << std::endl;
            std::cin.ignore(10000, '\n');
            std::cin.clear();
        }
    } while ((choice < 1) || (choice > 7));
    if (choice == 7) {
        return NULL;
    }
    else {
        return choice;
    }
}
int main()
{
    Line_descriptor sample;
    int answer = 0;
    while (answer = Get_answer()) {
        system("cls");
        f_ptrs[answer](sample);
        _getch();
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    }
    return 0;
}
