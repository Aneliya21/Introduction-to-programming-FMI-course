#include <iostream>

constexpr size_t MAX_SIZE = 64;
constexpr size_t SIZE_OF_BOOL_ARRAY = 8;
const bool INIT_VALUE = false;
const size_t MAX_SIZE_OF_BIN_MASK = 128;

void input(char* string) {

    if (!string) {
        std::cout << "Invalid input";
        return;
    }

    std::cin >> string;
}

void initBoolArray(bool* arr, bool initValue) {

    if (!arr) {
        std::cout << "Invalid input";
        return;
    }

    for (size_t i = 0; i < SIZE_OF_BOOL_ARRAY; i++) {
        arr[i] = initValue;
    }
}

void fillBoolArray(bool* arr, int digit) {

    if (!arr) {
        std::cout << "Invalid input";
        return;
    }

    size_t arrayIter = SIZE_OF_BOOL_ARRAY - 1;
    int mask = 1;

    while (digit != 0 && mask <= MAX_SIZE_OF_BIN_MASK) {

        if ((mask & digit) == mask) {
            arr[arrayIter] = 1;
        }

        arrayIter--;
        mask <<= 1;
    }

    for (int i = arrayIter; i >= 0; i--) {
        arr[i] = 0;
    }
}

void fillFirstBoolArray(const bool* arr, bool* first) {

    size_t iterCount = SIZE_OF_BOOL_ARRAY / 2;

    for (size_t i = 0, firstIter = 0; i < iterCount; i++, firstIter += 2) {

        if (arr[i] == 0) {
            first[firstIter] = 0;
            first[firstIter + 1] = 1;
        }

        else if (arr[i] == 1) {
            first[firstIter] = 1;
            first[firstIter + 1] = 0;
        }
    }
}

void fillSecondBoolArray(const bool* arr, bool* second) {

    size_t iterStart = SIZE_OF_BOOL_ARRAY / 2;

    for (size_t i = iterStart, secondIter = 0; i < SIZE_OF_BOOL_ARRAY; i++, secondIter += 2) {

        if (arr[i] == 0) {
            second[secondIter] = 0;
            second[secondIter + 1] = 1;
        }

        else if (arr[i] == 1) {
            second[secondIter] = 1;
            second[secondIter + 1] = 0;
        }
    }
}

int fromBinaryToDecimal(const bool* array) {
    int number = 0;
    for (int i = SIZE_OF_BOOL_ARRAY - 1, mult = 1; i >= 0; i--, mult *= 2) {

        number += (array[i] * mult);
    }
    return number;
}

unsigned myStrLen(const char* str) {
    if (!str) {
        return 0;
    }

    unsigned size = 0;
    while (*str) {
        size++;
        str++;
    }
    return size;
}

char* codeString(const char* string) {

    if (!string) {
        std::cout << "Invalid input";
        return nullptr;
    }

    bool arr[SIZE_OF_BOOL_ARRAY]{ false };
    bool first[SIZE_OF_BOOL_ARRAY]{ false };
    bool second[SIZE_OF_BOOL_ARRAY]{ false };

    unsigned stringLen = myStrLen(string);

    if (stringLen > MAX_SIZE) {
        std::cout << "Invalid input";
        return nullptr;
    }

    unsigned newStringLen = stringLen * 2;
    char* result = new char[newStringLen + 1];

    result[newStringLen] = '\0';

    unsigned resIter = 0;

    while (*string) {

        int currentNumber = (int)(*string);

        fillBoolArray(arr, currentNumber);

        fillFirstBoolArray(arr, first);
        fillSecondBoolArray(arr, second);

        result[resIter] = (char)(fromBinaryToDecimal(first));
        result[resIter + 1] = (char)(fromBinaryToDecimal(second));

        resIter += 2;
        string++;

        initBoolArray(arr, 0);
        initBoolArray(first, 0);
        initBoolArray(second, 0);
    }
    return result;
}

int main()
{
    char string[MAX_SIZE + 1];

    input(string);

    char* coded = codeString(string);

    std::cout << coded;

    delete[] coded;
}
