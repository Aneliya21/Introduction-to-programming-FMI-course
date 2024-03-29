#include <iostream>

size_t numLen(long N) {
	size_t len = 0;
	while (N != 0) {
		len++;
		N /= 10;
	}
	return len;
}

long* fromNumToArr(long N) {
	size_t nLen = numLen(N);
	long* res = new long[nLen];

	for (size_t i = 0; i < nLen; i++) {
		res[i] = N % 10;
		N /= 10;
	}
	return res;
}

void swap(long& a, long& b) {
	long temp = a;
	a = b;
	b = temp;
}

void reverseArr(long* arr, size_t size) {
	for (size_t i = 0; i < size / 2; i++) {
		swap(arr[i], arr[size - i - 1]);
	}
}

void removeElementFromArray(long* arr, size_t indexToRemove, size_t& size) {

	if (indexToRemove == size - 1) {
		size--;
	}
	for (size_t i = indexToRemove; i < size - 1; i++) {
		arr[i] = arr[i + 1];
	}
}

long fromArrToNum(const long* arr, size_t size) {
	long res = 0;
	for (size_t i = 0; i < size - 1; i++) {
		res *= 10;
		res += arr[i];
	}
	return res;
}

int checkNum(long N) {
	size_t len = numLen(N);
	long* arr = fromNumToArr(N);
	reverseArr(arr, len);
	for (size_t i = 0; i < len; i++) {
		removeElementFromArray(arr, i, len);
		long newN = fromArrToNum(arr, len);
		if (((newN / 3) * 3) == newN) {

			delete[] arr;

			return i + 1;
		}
	}

	delete[] arr;

	return 0;

}

int main() {
	std::cout << checkNum(337);
}
