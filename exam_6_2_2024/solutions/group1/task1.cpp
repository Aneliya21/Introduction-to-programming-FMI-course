#include <iostream>

int fromCharToInt(char ch) {
	return ch - '0';
}

bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

//1 2 3 4 5 6 7 8 9

int analyzeArray(const char* str) {
	if (!str) {
		std::cout << "Invalid input";
		return 0;
	}
	
	bool one = false, 
		two = false, 
		three = false, 
		four = false, 
		five = false, 
		six = false, 
		seven = false, 
		eight = false, 
		nine = false, 
		ten = false;

	while (*str) {
		if (isDigit(*str)) {
			int digit = fromCharToInt(*str);
			if (digit == 1) {
				one = true;
			}
			else if (digit == 2) {
				two = true;
			}
			else if (digit == 3) {
				three = true;
			}
			else if (digit == 4) {
				four = true;
			}
			else if (digit == 5) {
				five = true;
			}
			else if (digit == 6) {
				six = true;
			}
			else if (digit == 7) {
				seven = true;
			}
			else if (digit == 8) {
				eight = true;
			}
			else if (digit == 9) {
				nine = true;
			}

		}
		str++;
	}
	if (nine == false) {
		return 9;
	}
	else if (eight == false) {
		return 8;
	}
	else if (seven == false) {
		return 7;
	}
	else if (six == false) {
		return 6;
	}
	else if (five == false) {
		return 5;
	}
	else if (four == false) {
		return 4;
	}
	else if (three == false) {
		return 3;
	}
	else if (two == false) {
		return 2;
	}
	else if (one == false) {
		return 1;
	}
	else {
		return -1;
	}
}

int main() {
	char str[] = "fsh3vf1eff2ae4fa8sa9";
	std::cout << analyzeArray(str);
}
