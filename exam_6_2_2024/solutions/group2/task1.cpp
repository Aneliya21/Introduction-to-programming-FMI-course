#include <iostream>

long findSeq(const char* arr, char S) {
	if (!arr) {
		std::cout << "Invalid input";
		return 0;
	}
	long seq = 0;
	
	long maxSeq = 0;

	while (*arr) {
		if (*arr == S) {
			seq++;
			if (seq > maxSeq) {
				maxSeq = seq;
			}
		}
		else {
			seq = 0;
		}
		arr++;
	}
	return maxSeq;
}

int main() {
	std::cout << findSeq("vsssgrfssssefjvnsssss", 's');
}
