#include <iostream>

const size_t N_MAX = 256;
const size_t S_MAX = 127;

bool validationOfN(size_t n) {
    return n > 0 && n < N_MAX;
}

bool validationOfC(char c) {
    return c >= 'a' && c <= 'z';
}

bool validationOfS(size_t s) {
    return s >= 0 && s <= S_MAX;
}

void inputArr(char balls[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        std::cin >> balls[i];
    }
    std::cout << std::endl;
}

void inputShoots(size_t indexes[], char colors[], size_t s) {
    for (size_t i = 0; i < s; i++) {
        std::cin >> indexes[i];
        std::cin >> colors[i];
        //std::cout << std::endl;
    }
    std::cout << std::endl;
}

void initCharArr(char balls[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        balls[i] = '0';
    }
}

void initIndexArr(size_t indexes[], size_t s) {
    for (size_t i = 0; i < s; i++) {
        indexes[i] = 0;
    }
}

size_t getCountOfFollowingWithTheSameColor(const char balls[], size_t n, size_t firstIndexBeforeCoseq, char colorOfFirstIndexBeforeConseq) {
    size_t count = 0;
    for (size_t i = firstIndexBeforeCoseq + 1; i < n; i++) {
        if (balls[i] == colorOfFirstIndexBeforeConseq) {
            count++;
        }
        else {
            return count;
        }
    }
    return count;
}

size_t getCountOfPrevWithTheSameColor(const char balls[], size_t n, size_t firstIndexBeforeConseq, char colorOfFirstIndexBeforeConseq) {
    size_t count = 1;
    size_t i = firstIndexBeforeConseq - 1;
    while (balls[i--] == colorOfFirstIndexBeforeConseq) {
        count++;
    }
    return count;
}

size_t sumCountsOfFollowingAndPrev(const char balls[], size_t n, size_t firstIndexBeforeConseq, char colorOfFirstIndexBeforeConseq) {
    return getCountOfFollowingWithTheSameColor(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeConseq) + getCountOfPrevWithTheSameColor(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeConseq);
}

bool isNewConseqFormed(const char balls[], size_t n, size_t firstIndexBeforeConseq, char colorOfFirstIndexBeforeConseq) {
    if (getCountOfFollowingWithTheSameColor(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeConseq) == 0) {
        return false;
    }
    return sumCountsOfFollowingAndPrev(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeConseq) >= 3 && getCountOfFollowingWithTheSameColor(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeConseq) > 0;
}

void removeIfNewConseqFormed(char balls[], size_t& n, size_t& firstIndexBeforeConseq, char& colorOfFirstIndexBeforeConseq) {
    size_t count = sumCountsOfFollowingAndPrev(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeConseq);

    int i = firstIndexBeforeConseq - getCountOfPrevWithTheSameColor(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeConseq) + 1;
    for (int j = i; j < count; j++)
        balls[j] = balls[j + count];
    n -= count;

    firstIndexBeforeConseq = i - 1;
    colorOfFirstIndexBeforeConseq = balls[firstIndexBeforeConseq];

}

void shootBall(char balls[], size_t& n, size_t index, char color) {
    n++;

    for (int i = n - 1; i > index + 1; i--) {
        balls[i] = balls[i - 1];
    }
    balls[index + 1] = color;

    int i = index - 1;
    while (i >= 0 && balls[i] == color) { 
        i--;
    }

    i++;

    int count = 1;
    while (i + count < n && balls[i] == balls[i + count]) {
        count++;
    }

    if (count >= 3) {                        
        for (int j = i; j < n - count; j++)
            balls[j] = balls[j + count];
        n -= count;
    }

    /*while (isANewConseqFormed(balls, n, firstIndexBeforeConseq)) {
        removeIfANewConseqIsFormed(balls, n, firstIndexBeforeConseq);
    }*/

    size_t firstIndexBeforeConseq = i - 1;
    char colorOfFirstIndexBeforeCoseq = balls[firstIndexBeforeConseq];

    while (isNewConseqFormed(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeCoseq)) {
        removeIfNewConseqFormed(balls, n, firstIndexBeforeConseq, colorOfFirstIndexBeforeCoseq);
    }
}

void printBallsArray(char balls[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        std::cout << balls[i] << " ";
    }
}

void shootColorBalls(char balls[], size_t& n, size_t indArr[], char colorsArr[], size_t sizeOfIndAndColorArr) {

    for (size_t i = 0; i < sizeOfIndAndColorArr; i++) {
        if (n > 0) {
            shootBall(balls, n, indArr[i], colorsArr[i]);
        }
    }

}

int main()
{
    size_t n = 1, s = 0;
    char c = 'a';


    constexpr size_t size = N_MAX;
    char balls[size];
    initCharArr(balls, n);

    std::cin >> n;

    inputArr(balls, n);


    std::cin >> s;

    constexpr size_t sizeOfIndArr = S_MAX;
    size_t indArr[sizeOfIndArr];
    initIndexArr(indArr, s);

    constexpr size_t sizeOfColorsArr = S_MAX;
    char colorsArr[sizeOfColorsArr];
    initCharArr(colorsArr, s);

    inputShoots(indArr, colorsArr, s);

    shootColorBalls(balls, n, indArr, colorsArr, s);

    printBallsArray(balls, n);
}
