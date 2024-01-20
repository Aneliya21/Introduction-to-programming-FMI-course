#include <iostream>

int** input(int N) {
    int** matrix = new int* [N];
    for (int i = 0; i < N; ++i) {
        int M;
        std::cin >> M;

        matrix[i] = new int[M];

        for (int j = 0; j < M; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    return matrix;
}

void freeMemory(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int getMaxOfTwo(int first, int second) {
    if (first > second) {
        return first;
    }
    return second;
}

int findLongestIncreasingSequence(int** matrix, int rows, int cols, int i, int j, int prevValue) {
    
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        return 0;
    }
    
    if (matrix[i][j] > prevValue) {
        
        int up = 1 + findLongestIncreasingSequence(matrix, rows, cols, i - 1, j, matrix[i][j]);
        int down = 1 + findLongestIncreasingSequence(matrix, rows, cols, i + 1, j, matrix[i][j]);
        int left = 1 + findLongestIncreasingSequence(matrix, rows, cols, i, j - 1, matrix[i][j]);
        int right = 1 + findLongestIncreasingSequence(matrix, rows, cols, i, j + 1, matrix[i][j]);

        int upLeftDiag = 1 + findLongestIncreasingSequence(matrix, rows, cols, i - 1, j - 1, matrix[i][j]);
        int upRightDiag = 1 + findLongestIncreasingSequence(matrix, rows, cols, i - 1, j + 1, matrix[i][j]);
        int downLeftDiag = 1 + findLongestIncreasingSequence(matrix, rows, cols, i + 1, j - 1, matrix[i][j]);
        int downRightDiag = 1 + findLongestIncreasingSequence(matrix, rows, cols, i + 1, j + 1, matrix[i][j]);
        
        //int firstMax = getMaxOfFour(up, down, left, right);

        int maxBetwUpAndDown = getMaxOfTwo(up, down);
        int maxBetwLeftOrRight = getMaxOfTwo(left, right);

        int maxNeighbourOnLine = getMaxOfTwo(maxBetwUpAndDown, maxBetwLeftOrRight);

        //int secondMax = getMaxOfFour(upLeftDiag, upRightDiag, downLeftDiag, downRightDiag);

        int maxFromUpDiagonal = getMaxOfTwo(upLeftDiag, upRightDiag);
        int maxFromDownDiagonal = getMaxOfTwo(downLeftDiag, downRightDiag);

        int maxNeighbourOnDiagonals = getMaxOfTwo(maxFromUpDiagonal, maxFromDownDiagonal);

        return getMaxOfTwo(maxNeighbourOnLine, maxNeighbourOnDiagonals);
    }
    return 0;
}

int findMaxIncreasingSequenceLength(int** matrix, int rows, int cols) {
    
    int maxLength = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            int length = findLongestIncreasingSequence(matrix, rows, cols, i, j, -1);

            maxLength = getMaxOfTwo(maxLength, length);
        }
    }

    return maxLength;
}

int main() {
    int N;
    std::cin >> N;

    int** matrix = input(N);

    std::cout << findMaxIncreasingSequenceLength(matrix, N, N);

    freeMemory(matrix, N);

    return 0;
}
