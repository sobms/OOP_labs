#include "pch.h"
#include "./Big_decimal.h"
#include <string>
#include <string.h>
#include <algorithm> 
#define MAX_LENGTH 27
namespace lab_oop3 {
	Big_decimal::Big_decimal() : len(1) {
		if (this->max_len > 0)            // освобождать память перед вызовом конструктора+
			this->~Big_decimal();
		max_len= MAX_LENGTH;
		decimal_num = new char[max_len];
		for (int i = 0; i < max_len; i++) {
			decimal_num[i] = '0';
		}
	}

	Big_decimal::Big_decimal(long num) { 
		if (this->max_len > 0)            // освобождать память перед вызовом конструктора+
			this->~Big_decimal();
		int l = length(num);
		len = l;
		max_len = (l / MAX_LENGTH + 1) * (MAX_LENGTH);
		decimal_num = new char[max_len];
		decimal_num[0] = ((num < 0) ? '1' : '0'); // sign of the number
		if (num < 0) { num *= -1; }
		for (int i = 1; i < max_len; i++) {
			decimal_num[i] = (num % 10) + '0';
			if ((num /= 10) == 0) {
				break;
			}
		}
		for (int i = len + 1; i < max_len; i++) {
			decimal_num[i] = '0';
		}
	}
	Big_decimal::Big_decimal(const Big_decimal& sample) {
		if (sample.len>0) {
			len = sample.len;
			if (this->max_len > 0)            // освобождать память перед вызовом конструктора+
				this->~Big_decimal(); 
			max_len = sample.max_len;
			decimal_num = new char[max_len];
			for (int i = 0; i < max_len; i++) {
				decimal_num[i] = sample.decimal_num[i];
			}
		}else{ this->Big_decimal::Big_decimal(); }
	}

	Big_decimal::Big_decimal(std::string& str) : max_len(MAX_LENGTH) {
		//throw away zeros
		for (int i = 0; ((str[i] == '0') && (str.length()>1));) {
			str.erase(0,1);
		}
		//check if not a number
		if (!is_number(str)) {
			throw std::invalid_argument("string is not a number");
		}
		
		//get sign
		int sign = 0;
		if (str[0] == '-') {
			sign = 1;
			str.erase(0, 1);
		}

		//throw away zeroes
		for (int i = 0; ((str[i] == '0') && (str.length() > 1));) {
			str.erase(0, 1);
		}
		//get length of number
		int l = str.length();
		//form Big_decimal

		if (((l==1)&&(str[0]=='0'))||(l<1)) {
			max_len = 0;
			this->Big_decimal::Big_decimal();
			return;
		}
		//get necessary max_len
		max_len = (l / MAX_LENGTH + 1)*(MAX_LENGTH);  // вычислить размер делением без цикла+
		decimal_num = new char[max_len];	// memory allocation
		decimal_num[0] = ((sign == 1) ? '1' : '0');
		len = l;
		for (int i = 1; i <= l; i++) {
			decimal_num[i] = str[l - i];
		}
		for (int i = len + 1; i < max_len; i++) {
			decimal_num[i] = '0';
		}
	}
	std::ostream& operator << (std::ostream& out, const Big_decimal& a) {
		if (a.decimal_num[0] == '1') {
			out << '-';
		}
		for (int i = a.len; i > 0; i--) {
			out << (a.decimal_num[i]);
		}
		out << std::endl;
		return out;
	}
	std::istream& operator >> (std::istream& in, Big_decimal& a) { // обработка ошибок ввода+
		std::string str;
		std::cin >> str;
		if (std::cin.good()) {
			if (check_str(str)) {
				if (a.max_len>0) {
					a.~Big_decimal();				// освобождать память перед вызовом конструктора+
				}
				a.Big_decimal::Big_decimal(str);
			}
			else {
				in.setstate(std::ios::failbit);
			}
		}
		return in;
	}

	Big_decimal Big_decimal::operator~() const {
		if (decimal_num[0] == '0') {
			return *this;
		}
		else {
			Big_decimal new_num(*this);     // копирующий конструктор вместо ручного копирования+
			//new_num.decimal_num[0] = '1';
			for (int i = 1; i < max_len; i++) {
				new_num.decimal_num[i] = ('9' - decimal_num[i]) + '0';
			}
			new_num.Unsigned_Sum(Big_decimal(1));
			return new_num;
		}
	}
	Big_decimal& Big_decimal::operator =(const Big_decimal& a)  {
		if (this != &a) {
			delete[] decimal_num;
			decimal_num = nullptr;
			if (a.max_len > 0) {
				decimal_num = new char[a.max_len]; 
				if (decimal_num) { // проверить на то, что память выделилась нормально и изменить max_len+
					for (int i = 0; i < a.max_len; i++) {
						decimal_num[i] = a.decimal_num[i];
					}
					max_len = a.max_len;
					len = a.len;
				}
			}
			
		}
		return *this;
	}
	Big_decimal& Big_decimal::operator =(Big_decimal&& a) {
		if (this != &a) {
			delete[] decimal_num;
			max_len = a.max_len;
			len = a.len;
			decimal_num = a.decimal_num;
			a.decimal_num = nullptr;
		}
		return *this;
	}
	const Big_decimal operator +(const Big_decimal& a, const Big_decimal& b) { // выделение памяти вместо ошибки переполнения+
		Big_decimal result = ~a;
		Big_decimal second = ~b;
		int ovfl = result.Unsigned_Sum(second);
		int sign = ((a.decimal_num[0] - '0') + (second.decimal_num[0] - '0') + ovfl) % 2;
		if (a.decimal_num[0] == b.decimal_num[0]) {
			sign = a.decimal_num[0]-'0';
		}
		result.decimal_num[0] = sign + '0';
		result =(~result);

		result.len = 1;
		for (int i = result.max_len - 1; i > 0; i--) {
			if (result.decimal_num[i] != '0') {
				result.len = i;
				break;
			}
		}
		if (result.len < result.max_len - MAX_LENGTH) {
			result.max_len -= MAX_LENGTH;
			char* new_num = new char[result.max_len]; // если адресат const, то перемещение исключено, а для копирования нужно изменить max_len, что запрещено
			for (int i = 0; i < result.max_len; i++) {
				new_num[i] = result.decimal_num[i];
			}
			delete[] result.decimal_num;
			result.decimal_num = new_num;
		}
		return result;
	}
	const Big_decimal operator -(const Big_decimal& a, const Big_decimal& b) {
		Big_decimal copy(b);
		copy.decimal_num[0] = ((copy.decimal_num[0] == '0') ? '1' : '0');
		return (a) + copy;
	}
	void Big_decimal::Prod_ten(Big_decimal& res) const{
		
		if (len == (max_len - 1)) {              //увеличение памяти, если число на границе max_len+
			res.max_len += MAX_LENGTH;
			delete[]res.decimal_num;
			res.decimal_num = new char[res.max_len]; // если адресат const, то перемещение исключено, а для копирования нужно изменить max_len, что запрещено
			for (int i = 0; i < max_len; i++) {
				res.decimal_num[i] = decimal_num[i];
			}
			for (int i = max_len; i < res.max_len; i++) {
				res.decimal_num[i] = '0';
			}
		}

		if (res.decimal_num[len] == '0') {
			return;
		}
		for (int i = len; i > 0; i--) {
			res.decimal_num[i + 1] = res.decimal_num[i];
		}
		res.decimal_num[1] = '0';
		res.len++;
	}
	void Big_decimal::Div_ten(Big_decimal& res) const {
		for (int i = 1; i < len; i++) {
			res.decimal_num[i] = res.decimal_num[i + 1];
		}
		res.decimal_num[len] = '0';
		if (res.len == 1) {
			res.decimal_num[0] = '0';
			return;
		}
		if (len % MAX_LENGTH==0) {		//уменьшение выделенной памяти+
			res.max_len -= MAX_LENGTH;  // если адресат const, то перемещение исключено, а для копирования нужно изменить max_len, что запрещено
			char* new_num = new char[res.max_len];
			for (int i = 0; i < res.max_len; i++) {
				new_num[i] = res.decimal_num[i];
			}
			delete[]res.decimal_num;
			res.decimal_num = new_num;
		}
		res.len--;
	}
	//supporting methods
	int lab_oop3::length(long num) {
		int len = 0;
		do {
			++len;
			num /= 10;
		} while (num != 0);
		return len;
	}
	int Big_decimal::Unsigned_Sum(const Big_decimal& a) {
		int overflow = 0, ovfl = 0;
		len = std::max(len, a.len);

		int max_l = std::max(max_len, a.max_len);
		if ((len == (max_len - 1))&&(a.decimal_num[0]==decimal_num[0])) {   //если массив может переполниться+
			max_l += MAX_LENGTH;
		}
		Big_decimal new_a = a;
		new_a.Get_mem(max_l);
		new_a.max_len = max_l;

		this->Get_mem(max_l); // функция расширения памяти на size
		for (int i = 1; (i < new_a.max_len); i++) {
			int sum = int((decimal_num[i] - '0')) + int((new_a.decimal_num[i] - '0')) + overflow;
			decimal_num[i] = (sum % 10) + '0';
			overflow = ((sum >= 10) ? 1 : 0);
			if (i == len) {
				ovfl = overflow;
			}
		}
		/*if ((ovfl) && (len == (max_len- MAX_LENGTH - 1))) {
																//если массив переполняется
			decimal_num[len+1]='1';
		}*/
		return ovfl;
	}
	bool lab_oop3::is_number(std::string& str) {
		int i, length;
		length = str.length();
		for (i = 0; (i < length && (isdigit(str[i]) || ((i == 0) && (str[i] == '-')))); i++);
		if (i == length) {
			return true;
		}
		else { return false; }
	}
	bool lab_oop3::check_str(std::string& str) {
		//throw away zeros
		for (int i = 0; ((str[i] == '0')&&(str.length()>1));) {
			str.erase(0, 1);
		}
		//check if not a number
		if (!is_number(str)) {
			return false;
		}
		else {
			return true;
		}
	}
	Big_decimal& Big_decimal::Get_mem(int size) {
		if (max_len < size) {
			char* new_ptr = new char[size];
			for (int i = 0; i < max_len; i++) {
				new_ptr[i] = decimal_num[i];
			}
			char d = ((decimal_num[0] == '0') ? '0' : '9');
			for (int i =max_len; i < size; i++) {
				new_ptr[i] = d;
			}
			max_len = size;
			delete[] decimal_num;
			decimal_num = new_ptr;
		}
		return *this;
	}
	bool Big_decimal::compare_numbers(const char* str2) {
		if (strlen(str2) == max_len) {
			for (int i = 0; i < max_len; i++) {
				if (decimal_num[i] != str2[i]) {
					return false;
				}
			}
		}
		else { return false; }
		return true;
	}
}