#include <iostream>

bool isSymbol(char ch) {
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

bool isPatternOnlyPercents(const char* pattern) {
	while (*pattern) {
		if (*pattern == '%') {
			pattern++;
		}
		else return false;
	}
	return true;
}

bool isPatternOnlyWithPercentsAndStar(const char* pattern, unsigned& countOfPercents, unsigned& countOfStars) {
	while (*pattern) {
		if (*pattern == '%') {
			countOfPercents++;
		}
		else if (*pattern == '*') {
			countOfStars++;
		}
		else {
			return false;
		}
	}
	return true;
}

void getIndexesOfPercentsInPatternWithPercentsAndStars(const char* pattern, int* indexesOfPercents, int* indexesOfStars) {
	unsigned patternInd = 0;
	unsigned indexesOfPerInd = 0;
	unsigned indexesOfStarsInd = 0;
	while (pattern[patternInd] != '\0') {
		if (pattern[patternInd] == '%') {
			indexesOfPercents[indexesOfPerInd++] = patternInd;
		}
		else if (pattern[patternInd] == '*') {
			indexesOfStars[indexesOfStarsInd++] = patternInd;
		}
		patternInd++;
	}
}

//taken from: https://github.com/Angeld55/Introduction_to_programming_FMI/blob/main/Sem.%2010/search_in_text.cpp and modified
bool isPrefix(const char* pattern, const char* text)
{
	if (!pattern || !text) {
		std::cout << "Invalid input";
		return false;
	}
	while (*text != '\0' && *pattern != '\0')
	{
		if (*text == *pattern) {
			text++;
			pattern++;
		}
		else if (*pattern == '*') {
			text++;
			pattern++;
		}
		else if (*pattern == '@' && isSymbol(*text)) {
			text++;
			pattern++;
		}
		else if (*pattern == '%' && isDigit(*text)) {
			text++;
			if (isDigit(*text)) {
				text++;
				pattern++;
				continue;
			}
			pattern++;
		}
		else return false;
	}
	return *pattern == '\0';
}

unsigned myStrLen(const char* str) {
	if (!str) {
		return 0;
	}
	unsigned len = 0;
	while (*str) {
		len++;
		str++;
	}
	return len;
}

char** getMasksOfPattern(const char* pattern, unsigned patternLen) {

	if (!pattern) {
		std::cout << "Invalid input";
		return nullptr;
	}

	unsigned rowsSize = patternLen + 2;

	char** masks = new char* [rowsSize];

	masks[rowsSize - 1] = nullptr;
	
	for (int i = 0; i < rowsSize - 1; i++) {
		masks[i] = new char[patternLen + i];
	}
	for (int rows = 0; rows < rowsSize - 1; rows++) {
		for (int colls = 0; colls < patternLen + rows; colls++) {
			masks[rows][colls] = '%';
		}
	}
	return masks;
}

unsigned countOfMaskInString(const char* mask, unsigned maskSize, const char* str, unsigned strSize) {
	unsigned count = 0;
	unsigned maskInd = 0;
	unsigned strInd = 0;

	if (maskSize == strSize) {
		return 1;
	}
	else if (maskSize > strSize) {
		return 0;
	}
	while (strInd < strSize - 1) {
		while (maskInd < maskSize - 1) {
			if (isDigit(str[strInd])) {
				strInd++;
				maskInd++;
			}
		}
		if (isDigit(str[strInd])) {
			strInd-=(maskSize - 2);
		}
		count++;
		maskInd = 0;
	}
	if (maskSize == strSize - 1) {
		return count - 1;
	}
	return count;
}

unsigned countOfPatternInStringInCaseOfPercent(const char* str, const char* pattern) {

	if (!str || !pattern) {
		std::cout << "Invalid input";
		return 0;
	}

	unsigned patternLen = myStrLen(pattern);
	unsigned strLen = myStrLen(str);
	if (patternLen == strLen) {
		return 1;
	}
	else if (patternLen > strLen) {
		return 0;
	}
	char** masksOfPattern = getMasksOfPattern(pattern, patternLen);
	unsigned rowsInMasksOfPattern = patternLen + 2;

	unsigned counter = 0;

	for (unsigned i = 0; i < rowsInMasksOfPattern; i++) {
		counter += countOfMaskInString(masksOfPattern[i], patternLen + i, str, strLen);
	}

	for (int i = 0; masksOfPattern[i] != nullptr; i++) {
		delete[] masksOfPattern[i];
	}
	delete[] masksOfPattern;

	return counter;
}

unsigned sizeOfCharArrayForNumberInText(const char* str, unsigned currentStartIndex, unsigned strSize) {

	if (!str) {
		std::cout << "Invalid input";
		return 0;
	}

	unsigned size = 1;
	for (unsigned i = currentStartIndex + 1; i < strSize; i++) {
		if (isDigit(str[i])) {
			size++;
		}
		else {
			return size;
		}
	}
	return size;
}

void fillArrayWithNumber(const char* str, unsigned currentIndex, char* arr, unsigned sizeOfArr) {
	if (!str || !arr) {
		std::cout << "Invalid input";
		return;
	}
	unsigned diapason = currentIndex + (sizeOfArr - 1);
	for (unsigned i = currentIndex, j = 0; i <= diapason; i++, j++) {
		arr[j] = str[i];
	}
	arr[sizeOfArr] = '\0';
}

unsigned countOfPatternInString(const char* str, const char* pattern) {

	unsigned countOfPercents = 0;
	unsigned countOfStars = 0;

	if (!str || !pattern) {
		std::cout << "Invalid input";
		return 0;
	}

	unsigned counter = 0;

	size_t textLen = myStrLen(str);
	size_t patternLen = myStrLen(pattern);

	if (!isPatternOnlyPercents(pattern) && !isPatternOnlyWithPercentsAndStar(pattern)) {
		while (patternLen <= textLen)
		{
			if (isPrefix(pattern, str))
				counter++;
			str++;
			textLen--;
		}
	}
	else if (isPatternOnlyPercents(pattern)) {
		//take the numbers it finds in the str and pass them to the func, instead of str

		for (unsigned i = 0; i < textLen; i++) {
			if (isDigit(str[i])) {
				//count the memory if should use
				unsigned sizeOfNumberArray = sizeOfCharArrayForNumberInText(str, i, textLen);

				char* currNumArr = new char[sizeOfNumberArray + 1];

				//fill the array with the number
				fillArrayWithNumber(str, i, currNumArr, sizeOfNumberArray);

				i += sizeOfNumberArray - 1;

				counter += countOfPatternInStringInCaseOfPercent(currNumArr, pattern);

				delete[] currNumArr;
			}
		}
	}

	else if (isPatternOnlyWithPercentsAndStar(pattern, countOfPercents, countOfStars)) {
		int* percentIndexes = new int[countOfPercents];
		int* starIndexes = new int[countOfStars];

		getIndexesOfPercentsInPatternWithPercentsAndStars(pattern, percentIndexes, starIndexes);
                 ////
		return 0;

	}
	return counter;
}

int main()
{
	char str[] = "123";

	char pattern[] = "%%*";

	std::cout << countOfPatternInString(str, pattern);
}
