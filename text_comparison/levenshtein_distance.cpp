#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

constexpr int COST_DELETE = 1;
constexpr int COST_INSERT = 1;

constexpr int minSub(const int a, const int b) {
    return (a < b) ? a : b;
}

int min(const int a, const int b, const int c) {
    return minSub(minSub(a,b), c);
}

int calculateCell(int i, int j, int **matrix, const char source[], const char target[]) {
    return min(matrix[i - 1][j - 1] + (source[j - 1] == target[i - 1] ? 0 : 1), matrix[i][j - 1] + COST_DELETE, matrix[i - 1][j] + COST_INSERT);
}

int levenshteinDistance(const char source[], const char target[]) {
    const size_t targetLength = strlen(target);
    const size_t sourceLength = strlen(source);

    int **matrix = new int*[targetLength + 1];
    for (int i = 0; i <= targetLength; i++) {
        matrix[i] = new int[sourceLength + 1];
    }

    for (int i = 0; i <= targetLength; i++) {
        matrix[i][0] = i;
    }

    for (int i = 0; i <= sourceLength; i++) {
        matrix[0][i] = i;
    }

    for (int i = 1; i <= targetLength; i++) {
        for (int j = 1; j <= sourceLength; j++) {
            matrix[i][j] = calculateCell(i, j, matrix, source, target);
        }
    }

    int returnValue = matrix[targetLength][sourceLength];

    for (int i = 0; i <= targetLength; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return returnValue;
}


int main() {
    const char source[] = "lssadnjasdbausbfuasfas";
    const char target[] = "dsfdsfdsfdsfsdfdsfdsfd";

    cout << "Levenshtein distance: " << levenshteinDistance(source, target) << endl;

    return 0;
}