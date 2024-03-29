#include <iostream>

unsigned int getCountOfDividers(unsigned int number) {
    unsigned int counter = 0;

    for (unsigned int i = 1; i <= number; i++) {
        if (number % i == 0) {
            counter++;
        }
    }

    return counter;
}

unsigned int multiplicateLhs(unsigned int k, unsigned int div_x, unsigned int div_y) {
    return k * div_x * div_y;
}

unsigned int multiplicateRhs(unsigned int x, unsigned int y) {
    return x * y;
}

unsigned int getCountOfPairs(unsigned int n, unsigned int k) {

    unsigned int counter = 0;

    for (unsigned int x = 1; x <= n; x++) {
        for (unsigned int y = x; y <= n; y++) {
            unsigned int div_x = getCountOfDividers(x);
            unsigned int div_y = getCountOfDividers(y);
            if (multiplicateLhs(k, div_x, div_y) == multiplicateRhs(x, y)) {
                counter++;
            }
        }
    }

    return counter;
}

int main()
{
    unsigned int n = 0, k = 0;
    std::cin >> n >> k;
    std::cout << getCountOfPairs(n, k);
}
