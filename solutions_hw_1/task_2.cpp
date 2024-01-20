#include <iostream>

const unsigned int MIN = 1;
const unsigned int MAX = 1000;
const unsigned int INIT_VALUE = 0;

bool isValidN(unsigned int n) {
    return n >= MIN && n <= MAX;
}

void inputArr(unsigned int arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
}

void initArr(unsigned int arr[], size_t size, unsigned int value) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = value;
    }
}

bool areAllEqualToOne(unsigned int arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == 1) {
            continue;
        }
        return false;
    }
    return true;
}

unsigned int getMinNumberOfCitizensOfUplandia(unsigned int arr[], size_t size) {
    unsigned int minNumberCitizens = 0;

    if (areAllEqualToOne(arr, size) && size > 1) {
        return minNumberCitizens += size;
    }

    for (size_t i = 0; i < size; i++) {

        if (i == 0) {
            minNumberCitizens++;
            minNumberCitizens += arr[i];
            continue;
        }
        if (arr[i] == arr[i - 1]) {
            continue;
        }
        
        minNumberCitizens++;
        minNumberCitizens += arr[i];
    }

    return minNumberCitizens;
}


int main()
{
    unsigned int n = 0;
    std::cin >> n;

    if (!isValidN(n)) {
        std::cout << "Invalid input";
    }

    constexpr size_t size = 1000;
    unsigned int arr[size];

    initArr(arr, n, INIT_VALUE);

    inputArr(arr, n);

    std::cout << getMinNumberOfCitizensOfUplandia(arr, n);
}
