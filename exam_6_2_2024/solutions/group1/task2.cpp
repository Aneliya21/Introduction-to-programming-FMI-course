*#include <iostream>

void countOfSmallerThanCount(const int arr[], size_t size, size_t i, int& count) {
	for (size_t j = 0; j <= i; j++) {
		if (arr[j] < count) {
			count--;
		}
	}
}

int findIndex(const int arr[], size_t size) {
	int count = 0;
	int maxCount = 0;
	int indexOfLast = 0;
	for (size_t i = 0; i < size; i++) {
		if (arr[i] >= count) {
			count++;
		}
		
		if (count > maxCount) {
			maxCount = count;
			indexOfLast = i;
		}
		if (arr[i] < count) {
			count = 0;
		}
	}
	countOfSmallerThanCount(arr, size, indexOfLast, maxCount);
	return maxCount;
}

//3 5 4 4 6 3
//

int main() {
	int arr[] = { 3, 5, 4, 4, 6,3};
	std::cout << findIndex(arr, 5);
}
