#include <iostream>

unsigned myStrLen(const char* str) {
    unsigned len = 0;
    while (*str) {
        len++;
        str++;
    }
    return len;
}

void swapTwoChars(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}

void sortString(char* str) {
    if (!str) {
        std::cout << "Invalid input";
        return;
    }

    unsigned strLen = myStrLen(str);

    //bubble sort
    for (unsigned i = 0; i < strLen - 1; i++) {
        for (unsigned j = 0; j < strLen - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                swapTwoChars(str[j], str[j + 1]);
            }
        }
    }
}

void myStrCpy(const char* source, char* dest) {
    if (!source || !dest) {
        std::cout << "Invalid input";
        return;
    }
    while (*source) {
        *dest = *source;
        dest++;
        source++;
    }
}

void printNext(char* arr, unsigned size) {

    if (!arr) {
        return;
    }

    int i = size - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i == -1) {
        return;
    }

    int j = size - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    swapTwoChars(arr[i], arr[j]);

    sortString(arr + i + 1);

    std::cout << arr << std::endl;

}

void sortAndPrint(const char* str, unsigned n) {

    if (!str) {
        std::cout << "Invalid input";
        return;
    }


    unsigned strLen = myStrLen(str);
    char* sortedString = new char[strLen + 1];

    sortedString[strLen] = '\0';

    myStrCpy(str, sortedString);

    sortString(sortedString);

    if (n == 1) {
        std::cout << sortedString;
        return;
    }

    std::cout << sortedString;
    std::cout << std::endl;

    for (unsigned i = 0; i < n - 1; i++) {
        printNext(sortedString, strLen);
    }

    delete[] sortedString;

}

int main()
{   
    char str[1024];
    std::cin.getline(str, 1024);

   sortAndPrint(str, 3);
}
