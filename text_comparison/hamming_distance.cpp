#include <iostream>
#include <cstring>

using namespace std;

int hammingDistance(const char source[], const char target[]) {
    const size_t sourceLen = strlen(source);
    if(sourceLen != strlen(target)) {
        throw invalid_argument("Source length is different than target lenght");
    }

    int counter = 0;
    for(int i = 0; i < sourceLen; i++) {
        if(source[i] != target[i]) {
            counter++;
        }
    }

    return counter;
}

constexpr int Cdel = 1;
constexpr int Cins = 1;

constexpr int minSub(const int a, const int b) {
    return a < b ? a : b;
}

int min(const int a, const int b, const int c) {
    return minSub(minSub(a,b), c);
}

int calculateCel(int i, int j, int **matrix, const char source[], const char target[]) {
    return min(matrix[i - 1][j - 1] + (source[j-1] == target[i-1] ? 0 : 1), matrix[i][j - 1] + Cdel, matrix[i - 1][j] + Cins);
}

int levelshteinDistance(const char source[], const char target[]) {
    const size_t targetLen = strlen(target);
    const size_t sourceLen = strlen(source);

    int *matrix[targetLen + 1];
    for (int i=0; i<=targetLen; i++) matrix[i] = new int[sourceLen + 1];

    for(int i = 0; i <= targetLen; i++) {
        matrix[i][0] = i;
    }

    for(int i = 0; i <= sourceLen; i++) {
        matrix[0][i] = i;
    }

    for(int i = 1; i <= targetLen; i++)
        for(int j = 1; j <= sourceLen; j++)
            matrix[i][j] = calculateCel(i, j, matrix, source, target);

    const int returnValue = matrix[targetLen][sourceLen];

    for(int i = 1; i <= targetLen; i++)
        delete[] matrix[i];

    return returnValue;
}

int calculateCel2(int i, int j, int *r0, int *r1, const char source[], const char target[]) {
    return min(r0[j - 1] + (source[j-1] == target[i-1] ? 0 : 1), r1[j - 1] + Cdel, r0[j] + Cins);
}

int levelshteinDistance2(const char source[], const char target[]) {
    const size_t targetLen = strlen(target);
    const size_t sourceLen = strlen(source);

    int *r0 = new int[sourceLen+1];
    int *r1 = new int[sourceLen+1];
    int *rtemp;

    for(int i = 0; i <= sourceLen; i++) r0[i] = i;

    for(int i = 1; i <= targetLen; i++) {
        r1[0] = i;
        for(int j = 1; j <= sourceLen; j++)
            r1[j] = calculateCel2(i, j, r0, r1, source, target);
        rtemp = r0;
        r0 = r1;
        r1 = rtemp;
    }

    int returnValue = r0[sourceLen];
    delete[] r0;
    delete[] r1;

    return returnValue;
}

int main() {
    const char source[] = "lssadnjasdbausbfuasfas";
    const char target[] = "dsfdsfdsfdsfsdfdsfdsfd";

    printf("Hamming's distance: %d\n", hammingDistance(source, target));
    printf("Levelshtein's distance: %d\n", levelshteinDistance(source, target));
    printf("Levelshtein's 2 distance: %d\n", levelshteinDistance2(source, target));

    return 0;
}
