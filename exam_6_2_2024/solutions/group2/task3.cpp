#include <iostream>

bool isValidN(size_t N) {
	return N > 0 && N <= 32;
}

size_t powerOfTwo(size_t n) {
	return 1 << n;
}

void fillArrayWithSubsets(const int arr[], size_t N, int result[], size_t& resultIndex, size_t mask) {
	for (int i = N-1; i >=0; i--) {
		if (mask % 2 != 0) {
			result[resultIndex++] = arr[i];
		}
		mask /= 2;
	}
}

void generateSubSets(const int arr[], size_t N, int* result) {
	size_t pOfTwo = powerOfTwo(N);
	size_t resInd = 0;
	for (size_t i = 1; i < pOfTwo; i++) {
		fillArrayWithSubsets(arr, N, result, resInd, i);
		resInd++;
		//result[resInd] = 0;
	}
}


int* findSets(const int arr[], size_t N) {
	if (!isValidN(N)) {
		return nullptr;
	}
	size_t resSize = (powerOfTwo(N)-1)*N;
	int* res = new int[resSize];
	for (size_t i = 0; i < resSize; i++) {
		res[i] = 0;
	}
	generateSubSets(arr, N, res);
	return res;
}

void printArr(const int* res, size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << res[i] << " ";
	}
}

int main() {
	int arr[] = { 1,2,3, 4 };
	int* res = findSets(arr, 4);
	printArr(res, 47);

	delete[] res;
	return 0;
}
