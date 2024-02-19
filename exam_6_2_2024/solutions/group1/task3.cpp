#include <iostream>

unsigned getAbsoluteValue(int n) {
	return (n >= 0) ? n : -n;
}

long getMax(long a, long b) {
	if (a > b) {
		return a;
	}
	return b;
}

void getPair(const long arr[], size_t N, long& num1, long& num2) {

	unsigned currentDiff = 0;
	unsigned smallestDiff = 10000;
	for (size_t i = 0; i < N; i++) {
		for (size_t j = i + 1; j < N; j++) {
			int currNotAbsolute = arr[i] - arr[j];
			currentDiff = getAbsoluteValue(currNotAbsolute);

			if (currentDiff < smallestDiff) {
				smallestDiff = currentDiff;
				
				if (arr[i] > arr[j]) {
					num1 = arr[i];
					num2 = arr[j];
				}
				else if (arr[j > arr[i]]) {
					num1 = arr[j];
					num2 = arr[i];
				}
			}
		}
	}
}

size_t getLenOfNum(long n) {
	size_t len = 0;
	while (n != 0) {
		len++;
		n /= 10;
	}
	return len;
}

long reverseNumber(long n) {
	long rev = 0;
	while (n != 0) {
		rev *= 10;
		rev += n % 10;
		n /= 10;
	}
	return rev;
}

char* findDiff(const long arr[], size_t N) {
	long n1 = 0, n2 = 0;
	getPair(arr, N, n1, n2);
	size_t lenOfn1 = getLenOfNum(n1);
	size_t lenOfn2 = getLenOfNum(n2);
	size_t sizeOfCharArray = lenOfn1 + lenOfn2 + 1;
	char* result = new char[sizeOfCharArray + 1];
	result[sizeOfCharArray] = '\0';
	result[lenOfn1] = ',';

	long revN1 = reverseNumber(n1);
	long revN2 = reverseNumber(n2);

	size_t i = 0;
	for (i = 0; i < lenOfn1; i++) {
		result[i] = ((revN1 % 10) + '0');
		revN1 /= 10;
	}

	for (size_t j = i + 1 ; j < sizeOfCharArray; j++) {
		result[j] = ((revN2 % 10) + '0');
		revN2 /= 10;
	}
	return result;
}

int main() {
	long arr[] = { 5,1,2,10 };
	char* res = findDiff(arr, 5);
	std::cout << res;
	delete[] res;
}
