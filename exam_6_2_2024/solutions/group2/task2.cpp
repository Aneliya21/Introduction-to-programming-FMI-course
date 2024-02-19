#include <iostream>

size_t myStrLen(const char* word) {
	size_t len = 0;
	while (*word) {
		len++;
		word++;
	}
	return len;
}

bool isOnHorizontLine(const char* grid, size_t N, const char* word) {
	size_t wordInd = 0;
	size_t wordLen = myStrLen(word);
	for (size_t i = 0; i < N; i++) {
		if (grid[i] == word[wordInd]) {
			if (wordInd == (wordLen - 1)) {
				return true;
			}
			wordInd++;
		}
		else {
			wordInd = 0;
		}
	}
	return false;
}

bool isOnHorizontal(const char* const* grid, size_t M, size_t N, const char* word) {
	for (size_t i = 0; i < M; i++) {
		if (isOnHorizontLine(grid[i], N, word)) {
			return true;
		}
	}
	return false;
}

bool isOnVertical(const char* const* grid, size_t M, size_t N, const char* word) {
	size_t wordInd = 0;
	size_t wordLen = myStrLen(word);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			
			if (grid[j][i] == word[wordInd]) {
				if (wordInd == (wordLen - 1)) {
					return true;
				}
				wordInd++;
			}
			else {
				wordInd = 0;
			}
		}
	}
	return false;
}

bool findWord(const char* const* grid, size_t M, size_t N, const char* word) {
	if (!grid || !word) {
		std::cout << "Invalid input";
		return false;
	}
	size_t wordLen = myStrLen(word);
	if (wordLen > M) {
		if (isOnHorizontal(grid, M, N, word)) {
			return true;
		}
		return false;
	}
	else if (wordLen > N) {
		if (isOnVertical(grid, M, N, word)) {
			return true;
		}
		return false;
	}
	else
		if (isOnHorizontal(grid, M, N, word) || isOnVertical(grid, M, N, word)) {
			return true;
		return false;
	}
}

int main() {

	const char* grid[3] = {
		"atet",
		"hmgg",
		"ghir"
	};
	
	std::cout << findWord(grid, 3, 4, "tgg");
}
