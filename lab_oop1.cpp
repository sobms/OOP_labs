#include <iostream>
#include "lab_oop1.h"
#include <Windows.h>

namespace lab1 {
	struct elem {
		int x, y, val;
	};
	void clear_matr(line* lines, int n) {
		for (int i = 0; i < n; i++) {
			delete[] lines[i].arr;
		}
		delete[] lines;
	}
	int search_in_arr(line* array, int n, int key) {
		int i = 0;
		int m = n - 1;
		while (i <= m) {
			int j = (i + m) / 2;
			if (array[j].x == key) {
				return j + 1;
			}
			if (array[j].x > key) {
				m = j - 1;
			}
			else if (array[j].x < key) {
				i = j + 1;
			}
		}
		return 0;
	}
	int search_in_arr(node* array, int n, int key) {
		int i = 0;
		int m = n - 1;
		while (i <= m) {
			int j = (i + m) / 2;
			if (array[j].y == key) {
				return j + 1;
			}
			if (array[j].y > key) {
				m = j - 1;
			}
			else if (array[j].y < key) {
				i = j + 1;
			}
		}
		return 0;
	}
	line* Insert(line* array, elem a, int& n) {
		int k;
		if (!array) {
			array = (line*)malloc(sizeof(line) * 1);
			n++;
			array[0].x = a.x;
			array[0].n_elem = 1;
			array[0].arr = (node*)malloc(sizeof(node) * 1);
			array[0].arr[0].val = a.val;
			array[0].arr[0].y = a.y;
		}
		else if (!(k = search_in_arr(array, n, a.x))) {
			array = (line*)realloc(array, sizeof(line) * (n + 1)); // есть ли замена в с++
			int i = n-1;
			n++;
			while ((i >= 0)&&(array[i].x > a.x)) {
				array[i + 1] = array[i];
				i--;
			}
			array[i + 1].x = a.x;
			array[i + 1].n_elem = 1;
			array[i + 1].arr = (node*)malloc(sizeof(node) * 1);
			array[i + 1].arr[0].val = a.val;
			array[i + 1].arr[0].y = a.y;
		}
		else {
			k--;
			node* arr = array[k].arr;
			int p;
			if (!(p = search_in_arr(arr, array[k].n_elem, a.y))) {
				array[k].arr = (node*)realloc(array[k].arr, sizeof(node) * (array[k].n_elem + 1));
				int i = array[k].n_elem-1;
				array[k].n_elem++;
				while ((i>=0)&&(array[k].arr[i].y > a.y)) {
					array[k].arr[i + 1] = array[k].arr[i];
					i--;
				}
				array[k].arr[i + 1].y = a.y;
				array[k].arr[i + 1].val = a.val;
			}
			else {
				return NULL;
			}
		}
		return array;
	}
	line* create_matr(size& s, int& n) {
		// ввод числа строк и столбцов массива
		
		const char* error = "";
		do {
			std::cout << error;
			std::cout << "Input number of lines and number of rows" << std::endl;
			if (Input_num(s.n) == -1 || Input_num(s.m) == -1) {
				return nullptr;
			}
			system("cls");
			error = "Please, input positive values\n";
			cin.clear()
		} while (s.n < 1 || s.m < 1);
		system("cls");

		int n_values = 0;
		system("cls");
		std::cout << "Input number of elements in matrix" << std::endl;
		std::cin >> n_values;
		system("cls");
		
		line* lines_mas = nullptr;
		int n_lines = 0;
		for (int i = 0; i < n_values; i++) {
			// ввод элемента a[x,y]
			error = "";
			elem a = { 0,0,0 };
			do {
				std::cout << error;
				std::cout << "Input x,y and val of a[x,y]" << std::endl;
				if ((Input_num(a.x) == -1) || (Input_num(a.y) == -1) || (Input_num(a.val) == -1)) {
					clear_matr(lines_mas, n_lines);
					return nullptr;
				}
				system("cls");
				error = "Index is out of range\n";
				cin.clear()
			} while ((a.x >= s.n) || (a.y >= s.m));
			// вставка элемента
			lines_mas = Insert(lines_mas, a, n_lines);
		} 
		n = n_lines;
		return lines_mas;
	}
	void print_null(elem prev, elem cur, size sz) {
		int x, y;
		x = prev.x;
		y = prev.y + 1;
		while (x < cur.x) {
			while (y < sz.m) {
				std::cout << 0 << " ";
				y++;
			}
			std::cout << std::endl;
			x++;
			y = 0;
		}
		
		while ((y < cur.y)&&(x<sz.n)) {
			std::cout << 0 << " ";
			y++;
		}
	}
	void output_matr(line* lines_mas, size sz, int n_lines) {
		elem prev = { 0, -1 }, cur = { 0, 0 };
		for (int i = 0; i < n_lines; i++) {
			node* arr = lines_mas[i].arr;
			for (int j = 0; j < lines_mas[i].n_elem; j++) {
				cur.x = lines_mas[i].x;
				cur.y = lines_mas[i].arr[j].y;
				print_null(prev, cur, sz);
				std::cout << lines_mas[i].arr[j].val << " ";
				prev.x = lines_mas[i].x;
				prev.y = lines_mas[i].arr[j].y;
			}
			if (prev.y==sz.m)
				std::cout << std::endl;
		}
		print_null(prev, { sz.n,sz.m,0 }, sz);
			
	}
	// расход памяти О(sum[1-n](n_elem)+max(n,m)) Худший расход памяти достигается при m>>n!!!
	// время работы О(n*m) (без хэш таблицы O(n*m^2))
	inline int hash(int k, int i, int n) {
		return k % n + i;
	}
	int* find_equal_elems(line* lines_mas, int n, size sz) {
		for (int i = 0; i < n; i++) {
			struct hash_t {
				int elem;
				int count;
			};
			// создаем хэш-таблицу
			hash_t* table = new hash_t[lines_mas[i].n_elem];
			// инициализируем её нулями
			for (int j = 0; j < lines_mas[i].n_elem; j++) {
				table[j].count = 0;
				table[j].elem = NULL;
			}
			for (int j = 0; j < lines_mas[i].n_elem; j++) {
				int p = 0;
				// хэшируем в таблицу элементы строки
				do {
					int ind = hash(lines_mas[i].arr[j].val, p, lines_mas[i].n_elem);
					if ((table[ind].count > 0) && (table[ind].elem != lines_mas[i].arr[j].val))
					{
						p++;
					}
					else {
						table[ind].count++;
						if (!table[ind].elem) {
							table[ind].elem = lines_mas[i].arr[j].val;
						}
						break;
					}
				} while (true);
			}
			// делаем пороход таблицы и ищем макс число одинаковых элементов в строке
			int max = 0;
			for (int j = 0; j < lines_mas[i].n_elem; j++) {
				if (table[j].count > max) {
					max = table[j].count;
				}
			}
			lines_mas[i].num_equal = max;
			// очищаем хэш-таблицу
			delete[] table;
		}

		// создать b
		int* b = new int[sz.n];
		int k = 0;
		for (int i = 0; i < n; i++) {
			while (k < lines_mas[i].x) {
				b[k] = 0;
				k++;
			}
			b[k] = lines_mas[i].num_equal;
			k++;
		}
		while (k < sz.n) {
			b[k] = 0;
			k++;
		}
		return b;
	}
}
		