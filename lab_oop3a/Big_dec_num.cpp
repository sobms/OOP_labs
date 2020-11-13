#include "pch.h"
#include "./big_dec_num.h"
#include <string>
#include <algorithm> 
namespace lab_oop3 {
	Big_dec_num::Big_dec_num() : len(1) {
			for (int i = 0; i < MAX_LEN; i++) {
				decimal_num[i] = '0';
			}
	}
	
	Big_dec_num::Big_dec_num(long num) {
		decimal_num[0] = ((num < 0) ? '1' : '0'); // sign of the number
		if (num < 0) { num *= -1; }
		int l = length(num);
		try {
			if (l > MAX_LEN-1) {
				throw std::length_error("length of number more then permissible length!");
			}
		}
		catch(std::length_error &error)
		{
			std::cerr << error.what() << std::endl;
		}
		len = l;
		for (int i = 1; i < MAX_LEN && num>0;i++) {
			decimal_num[i] = (num % 10)+'0';
			num /= 10;
		}
		for (int i = len + 1; i < MAX_LEN; i++) {
			decimal_num[i] = '0';
		}
	}
	Big_dec_num::Big_dec_num(const char* str){
		//throw away zeros
		for (int i = 0; str[i] == '0';) {/////???
			str = str + 1;
		}
		decimal_num[0] = '0';
		if (str[0]=='-') {
			decimal_num[0] = '1';
			str = str + 1;
		}
		int l = strlen(str);
		try {
			if (l > MAX_LEN - 1) {
				throw std::length_error("length of string more then permissible length!");
			}
			if (!is_number(str)) {
				throw std::invalid_argument("string is not a number");
			}
		}
		catch (std::length_error& error)
		{
			std::cerr << error.what() << std::endl;
		}
		catch (std::invalid_argument& error) {
			std::cerr << error.what() << std::endl;
		}
		len = l;
		for (int i = 1; i <= l; i++) {
			decimal_num[i] = str[l - i];
		}
		for (int i = len + 1; i < MAX_LEN; i++) {
			decimal_num[i] = '0';
		}
	}
	std::ostream& Big_dec_num::Output(std::ostream& out) const{
		if (decimal_num[0] == '1') {
			out << '-';
		}
		for (int i = len; i > 0; i--) {
			out << (decimal_num[i]);
		}
		out << std::endl;
		return out;
	}
	std::istream& Big_dec_num::Input(std::istream& in) {
		char str[MAX_LEN];
		in.getline(str, MAX_LEN-1);
		try {
			if (!is_number(str)) {
				throw std::invalid_argument("string is not a number");
			}
		}
		catch (std::invalid_argument& error) {
			std::cerr << error.what() << std::endl;
			return in;
		}
		decimal_num[0] = ((str[0] == '-') ? '1' : '0');
		int length = strlen(str);

		for (int i = 1; i <= length; i++) {
			decimal_num[i] = str[length - i];
		}
		for (int i = length + 1; i < MAX_LEN; i++) {
			decimal_num[i] = '0';
		}
		if (str[0] == '-') {
			length--;
		}
		len = length;
		return in;			
	}

	Big_dec_num Big_dec_num::To_add_code() const {
		if (decimal_num[0] == '0') {
			return *this;
		}
		else {
			Big_dec_num new_num;
			new_num.decimal_num[0] = '1';
			new_num.len = len;
			for (int i = 1; i <= MAX_LEN; i++) {//в обратный код
				new_num.decimal_num[i] = ('9' - decimal_num[i]) + '0';
			}
			new_num.Unsigned_Sum(Big_dec_num(1));
			return new_num;
		}
	}
	const Big_dec_num Big_dec_num::Add(const Big_dec_num& s) const {
		Big_dec_num result = Big_dec_num::To_add_code();
		Big_dec_num second = s.To_add_code();
		int ovfl= result.Unsigned_Sum(second);
		int sign = ((decimal_num[0]-'0') + (second.decimal_num[0]-'0') + ovfl)%2;
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
		result = result.To_add_code();

		result.len = 0;
		for (int i = MAX_LEN-1; i > 0; i--) {
			if (result.decimal_num[i] != '0') {
				result.len = i;
				break;
			}
		}
		return result;
	}
	const Big_dec_num Big_dec_num::Subtruct(const Big_dec_num& s) const {
		Big_dec_num copy(s);
		copy.decimal_num[0] = ((copy.decimal_num[0] == '0') ? '1' : '0');
		return (*this).Add(copy);
	}
	const Big_dec_num Big_dec_num::Prod_ten() const {
		try {
			if (len == (MAX_LEN - 1)) {
				throw std::range_error("Multiplication is impossible because the number has max length");
			}
		}
		catch (std::range_error& err) {
			std::cerr << err.what() << std::endl;
			return -1;
		}
		Big_dec_num copy(*this);
		for (int i = len; i > 0; i--) {
			copy.decimal_num[i + 1] = copy.decimal_num[i];
		}
		copy.decimal_num[1] = '0';
		copy.len++;
		return copy;
	}
	const Big_dec_num Big_dec_num::Div_ten() const {
		Big_dec_num copy(*this);
		for (int i = 1; i < len; i++) {
			copy.decimal_num[i] = copy.decimal_num[i+1];
		}
		copy.decimal_num[len] = '0';
		copy.len--;
		return copy;
	}
	//supporting methods
	template <class T>
	int Big_dec_num::length(T num) {
		int len = 0;
		while (num != 0) {
			num /= 10;
			len++;
		}
		return len;
	}
	int Big_dec_num::Unsigned_Sum(const Big_dec_num& a){
		int overflow = 0,ovfl=0;
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
	bool Big_dec_num::is_number(const char* str) {
		int i,length;
		length = strlen(str);
		for (i = 0; (i < length && (isdigit(str[i])||(str[i]=='-'))); i++)
		{
		}
		if (i == length) {
			return true;
		}
		else { return false; }
	}
}