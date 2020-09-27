#include <iostream>
#include "lab_oop1.h"

using namespace lab1;
int main() {
	line* matrix = nullptr;
	size sz = { 0,0 };
	int n_lines = 0;
	matrix = create_matr(sz, n_lines);
	std::cout << "Entered matrix: " << std::endl;
	output_matr(matrix, sz, n_lines);
	int* b = nullptr;
	b = find_equal_elems(matrix, n_lines, sz);
	std::cout << "Vector b: " << std::endl;
	for (int i = 0; i < sz.n; i++) {
		std::cout << b[i] << " ";
	}
	clear_matr(matrix, n_lines);
	delete[] b;
	return 0;
}