#include <iostream>

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void sortArray(int* arr, size_t len) {
	for (size_t i = 0; i < len; i++) {
		for (size_t j = i; j < len; j++) {
			if (arr[i] > arr[j]) {
				swap(arr[i], arr[j]);
			}
		}
	}
}

void sqareArr(int* arr, size_t len) {
	for (size_t i = 0; i < len; i++) {
		int sqaureOfCurrent = arr[i] * arr[i];
		arr[i] = sqaureOfCurrent;
	}
	sortArray(arr, len);
}

void print(const int* arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << arr[i] << ' ';
	}
}

int main() {
	int arr[] = { -5, 1, 6 };
	sqareArr(arr, 3);
	print(arr, 3);
}
