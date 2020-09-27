namespace lab1 {

	struct node {
		int y;
		int val;
	};
	struct line {
		int n_elem;
		int x;
		int num_equal;
		node* arr;
	};
	struct size {
		int n, m;
	};
	template <class T>
	int Input_num(T& n) {
		using namespace std;
		cin >> n;
		if (!cin.good()) {
			return -1;
		}
		return 1;
	}

	line* create_matr(size& num, int& n);
	void output_matr(line* lines_mas, size sz, int n_lines);
	int* find_equal_elems(line* lines_mas, int n, size sz);
	void clear_matr(line* lines, int n);
}