#include "pch.h"
#include "./Big_decimal.h"
#include <string>
#include <algorithm> 
namespace lab_oop3 {
	Big_decimal::Big_decimal() : len(1) {
		for (int i = 0; i < MAX_LEN; i++) {
			decimal_num[i] = '0';
		}
	}

	Big_decimal::Big_decimal(long num) {
		decimal_num[0] = ((num < 0) ? '1' : '0'); // sign of the number
		if (num < 0) { num *= -1; }
		int l = length(num);
		try {
			if (l > MAX_LEN - 1) {
				throw std::length_error("length of number more then permissible length!");
			}
		}
		catch (std::length_error& error)
		{
			std::cerr << error.what() << std::endl;
			(*this).Big_decimal::Big_decimal();
			return;
		}
		len = l;
		for (int i = 1; i < MAX_LEN; i++) {
			decimal_num[i] = (num % 10) + '0';
			if ((num /= 10) == 0) {
				break;
			}
		}
		for (int i = len + 1; i < MAX_LEN; i++) {
			decimal_num[i] = '0';
		}
	}
	Big_decimal::Big_decimal(const char* str) {
		//throw away zeros
		for (; *str == '0';) {
			str = str + 1;
		}
		//check if not a number
		try {
			if (!is_number(str)) {
				throw std::invalid_argument("string is not a number");
			}
		}
		catch (std::invalid_argument& error) {
			std::cerr << error.what() << std::endl;
			(*this).Big_decimal::Big_decimal();
			return;
		}
		//get sign
		if (str[0] == '-') {
			decimal_num[0] = '1';
			str = str + 1;
		}
		else { decimal_num[0] = '0'; }

		//throw away zeroes
		for (; *str == '0';) {
			str = str + 1;
		}
		//get length of number
		int l = strlen(str);
		//check if len more than max
		try {
			if (l > MAX_LEN - 1) {
				throw std::length_error("length of string more then permissible length!");
			}
		}
		catch (std::length_error& error)
		{
			std::cerr << error.what() << std::endl;
			(*this).Big_decimal::Big_decimal();
			return;
		}
		//form Big_decimal
		if (l < 1) {
			(*this).Big_decimal::Big_decimal();
			return;
		}
		len = l;
		for (int i = 1; i <= l; i++) {
			decimal_num[i] = str[l - i];
		}
		for (int i = len + 1; i < MAX_LEN; i++) {
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
	std::istream& operator >> (std::istream& in, Big_decimal& a) {
		char str[Big_decimal::MAX_LEN];
		in.getline(str, Big_decimal::MAX_LEN - 1);
		a.Big_decimal::Big_decimal(str);
		return in;
	}

	Big_decimal Big_decimal::operator~() const {
		if (decimal_num[0] == '0') {
			return *this;
		}
		else {
			Big_decimal new_num;
			new_num.decimal_num[0] = '1';
			new_num.len = len;
			for (int i = 1; i <= MAX_LEN; i++) {//в обратный код
				new_num.decimal_num[i] = ('9' - decimal_num[i]) + '0';
			}
			new_num.Unsigned_Sum(Big_decimal(1));
			return new_num;
		}
	}
	const Big_decimal Big_decimal::operator +(const Big_decimal& a) const {
		Big_decimal result = ~(*this);
		Big_decimal second = ~a;
		int ovfl = result.Unsigned_Sum(second);
		int sign = ((decimal_num[0] - '0') + (second.decimal_num[0] - '0') + ovfl) % 2;
		result.decimal_num[0] = sign + '0';
		if (decimal_num[0] == second.decimal_num[0]) {
			try {
				if ((decimal_num[0] == '0') && (result.decimal_num[0] == '1')) {
					throw std::overflow_error("Positive_overflow");
				}
				else if ((decimal_num[0] == '1') && (result.decimal_num[0] == '0')) {
					throw std::overflow_error("Negative_overflow");
				}
			}
			catch (std::overflow_error& err) {
				std::cerr << err.what() << std::endl;
				return -1;
			}
		}
		result = ~result;

		result.len = 1;
		for (int i = MAX_LEN - 1; i > 0; i--) {
			if (result.decimal_num[i] != '0') {
				result.len = i;
				break;
			}
		}
		return result;
	}
	const Big_decimal Big_decimal::operator -(const Big_decimal& a) const {
		Big_decimal copy(a);
		copy.decimal_num[0] = ((copy.decimal_num[0] == '0') ? '1' : '0');
		return (*this) + copy;
	}
	const Big_decimal Big_decimal::Prod_ten() const {
		try {
			if (len == (MAX_LEN - 1)) {
				throw std::range_error("Multiplication is impossible because the number has max length");
			}
		}
		catch (std::range_error& err) {
			std::cerr << err.what() << std::endl;
			return -1;
		}
		Big_decimal copy(*this);
		if (copy.decimal_num[len] == '0') {
			return copy;
		}
		for (int i = len; i > 0; i--) {
			copy.decimal_num[i + 1] = copy.decimal_num[i];
		}
		copy.decimal_num[1] = '0';
		copy.len++;
		return copy;
	}
	const Big_decimal Big_decimal::Div_ten() const {
		Big_decimal copy(*this);
		for (int i = 1; i < len; i++) {
			copy.decimal_num[i] = copy.decimal_num[i + 1];
		}
		copy.decimal_num[len] = '0';
		if (copy.len == 1) {
			copy.decimal_num[0] = '0';
			return copy;
		}
		copy.len--;
		return copy;
	}
	//supporting methods
	template <class T>
	int Big_decimal::length(T num) {
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
		for (int i = 1; i <= MAX_LEN; i++) {
			int sum = int((decimal_num[i] - '0') + (a.decimal_num[i] - '0') + overflow);
			decimal_num[i] = (sum % 10) + '0';
			overflow = ((sum >= 10) ? 1 : 0);
			if (i == len) {
				ovfl = overflow;
			}
		}

		return ovfl;
	}
	bool Big_decimal::is_number(const char* str) {
		int i, length;
		length = strlen(str);
		for (i = 0; (i < length && (isdigit(str[i]) || ((i == 0) && (str[i] == '-')))); i++)
		{
		}
		if (i == length) {
			return true;
		}
		else { return false; }
	}
}