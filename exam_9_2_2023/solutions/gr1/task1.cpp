#include <iostream>

unsigned countOfOccur(char ch, char* arr) {
	if (!arr) {
		return 0;
	}
	unsigned count = 0;
	
	while (*arr) {
		if (ch == *arr) {
			count++;
		}
		arr++;
	}
	return count;
}

int analyzeArr(char* arr) {
	if (!arr) {
		return -1;
	}

	int count = 0;

	while (*arr) {
		if (countOfOccur(*arr, arr) == 1) {
			count++;
		}
		arr++;
	}

	return count;
}

int main() {
	char arr[] = "gdsffffwwwww";
	std::cout << analyzeArr(arr);
}
