#include <iostream>

const int MAX = 1000000000;

bool isValidNum(long num) {
	return num < MAX;
}

int getNumLen(long N) {
	int len = 0;
	while (N != 0) {
		len++;
		N /= 10;
	}
	return len;
}

long* putInArray(long N, int nLen) {
	long* arr = new long[nLen];

	for (int i = 0; i < nLen; i++) {
		arr[i] = N % 10;
		N /= 10;
	}
	return arr;
}

void swap(long& a, long& b) {
	long temp = a;
	a = b;
	b = temp;
}

void reverseArr(long* arr, int len) {
	for (int i = 0; i < len / 2; i++) {
		swap(arr[i], arr[len - i - 1]);
	}
}

void swapPos(long* arr, unsigned int m, unsigned int l) {
	swap(arr[m], arr[l]);
}

long revertToNumber(const long* arr, int size) {
	long res = 0;
	for (int i = 0; i < size; i++) {
		res *= 10;
		res += arr[i];
	}
	return res;
}

int checkNum(long N, unsigned int m, unsigned int l) {
	if (!isValidNum) {
		return -1;
	}
	int numLen = getNumLen(N);
	long* arr = putInArray(N, numLen);
	reverseArr(arr, numLen);
	swapPos(arr, m, l);
	long newN = revertToNumber(arr, numLen);
	
	delete[] arr;

	return (((newN / 4) * 4) == newN);
}

int main() {
	std::cout << checkNum(2876, 2, 3);
}
