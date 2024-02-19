#include <iostream>
//0123456789
//DD.MM.YYYY

const size_t DATE_LEN = 10;

size_t myStrLen(char* str) {
	if (!str) {
		return 0;
	}
	size_t len = 0;

	while (*str) {
		str++;
		len++;
	}
	return len;
}

int getDay(char* date) {
	int res = 0;
	if ((date[0] - '0') != 0) {
		res += (date[0] - '0');
		res *= 10;
		res += (date[1] - '0');
	}
	else
		res += (date[1] - '0');
	return res;
}

int getMonth(char* date) {
	int res = 0;
	if ((date[0] - '0') != 0) {
		res += (date[3] - '0');
		res *= 10;
		res += (date[4] - '0');
	}
	else
		res += (date[4] - '0');
	return res;
}

int getYear(char* date) {
	int res = 0;
	if ((date[6] - '0') != 0 ) {
		res += (date[6] - '0');
		res *= 10;
		res += (date[7] - '0');
		res *= 10;
		res += (date[8] - '0');
		res *= 10;
		res += (date[9] - '0');
	}
	else if ((date[6] - '0') == 0 && (date[7] - '0') != 0 && (date[8] - '0') != 0 && (date[9] - '0') != 0) {
		res += (date[7] - '0');
		res *= 10;
		res += (date[8] - '0');
		res *= 10;
		res += (date[9] - '0');
	}
	else if ((date[6] - '0') == 0 && (date[7] - '0') == 0 && (date[8] - '0') != 0 && (date[9] - '0') != 0) {
		res += (date[8] - '0');
		res *= 10;
		res += (date[9] - '0');
	}
	else if ((date[6] - '0') == 0 && (date[7] - '0') == 0 && (date[8] - '0') == 0 && (date[9] - '0') != 0) {
		res += (date[9] - '0');
	}
	else
		return 0;
	return res;
}

bool isLeapYear(int year) {
	return (year % 4 == 0);
}

bool isValidDay(int day) {
	return day >= 1 && day <= 31;
}

bool isValidMonth(int month) {
	return month >= 1 && month <= 12;
}

bool isValidYear(int year) {
	return year >= 1 && year <= 2024;
}

bool isValidDate(int day, int month, int year) {

	if (isValidDay(day) && isValidMonth(month) && isValidYear(year)) {

		switch (month) {
		case 1:
			return day <= 31;
		case 2:
			if (isLeapYear(year)) {
				return day <= 29;
			}
			return day <= 28;
		case 3:
			return day <= 31;
		case 4:
			return day <= 30;
		case 5:
			return day <= 31;
		case 6:
			return day <= 30;
		case 7:
			return day <= 31;
		case 8:
			return day <= 31;
		case 9:
			return day <= 30;
		case 10:
			return day <= 31;
		case 11:
			return day <= 30;
		case 12:
			return day <= 31;
		}
	}
	return false;
}

int CheckDate(char* date) {
	if (!date) {
		return 0;
	}

	size_t dateLen = myStrLen(date);

	if (dateLen != DATE_LEN) {
		return false;
	}

	int day = getDay(date);
	int month = getMonth(date);
	int year = getYear(date);

	if (isValidDate(day, month, year) && date[2] == '.' && date[5] == '.') {
		return true;
	}
	return false;
}

int main() {
	char date[] = "29.02.2023";
	std::cout << CheckDate(date);
}
