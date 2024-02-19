#include <iostream>

bool isValidN(int N) {
	return N >= 2 && N <= 49;
}

bool isValidWord(const char* word) {
	if (!word) {
		return false;
	}
	while (*word) {
		if (((int)*word) >= 32 && ((int)*word) <= 126) {
			word++;
		}
		else {
			return false;
		}
	}
	return true;
}

size_t myStrLen(const char* str) {
	if (!str) {
		return 0;
	}
	size_t len = 0;
	while (*str) {
		len++;
		str++;
	}
	return len;
}

char* encodeWord(char* word, int N) {
	if (!word || !isValidN(N) || !isValidWord(word)) {
		return nullptr;
	}

	size_t len = myStrLen(word);
	char* encoded = new char[len + 1];
	encoded[len] = '\0';
	
	size_t encInd = 0;

	while (*word) {
		encoded[encInd++] = (char)(*word + N);
		word++;
	}

	return encoded;
}

int main() {
	char word[] = "abc";
	char* encoded = encodeWord(word, 2);

	std::cout << encodeWord(word, 2);
}
