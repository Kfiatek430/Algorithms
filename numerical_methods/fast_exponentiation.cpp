#include<iostream>

using namespace std;

unsigned long long fastExponentiation(int base, int exponent) {
    if (exponent == 1) return base;

    if (exponent & 1)
        return base * fastExponentiation(base, exponent - 1);
    else {
        unsigned long long half = fastExponentiation(base, exponent / 2);
        return half * half;
    }
}

long long fastExponentiationIterative(long long base, unsigned int exponent) {
    long long result = 1;
    while (exponent) {
        if (exponent & 1) result *= base;
        base *= base;
        exponent >>= 1;
    }
    return result;
}

int fastModularExponentiation(int base, unsigned int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent & 1) result = ((long long)(result % modulus) * (long long)(base % modulus)) % modulus;
        long long temp = base % modulus;
        temp *= temp;
        base = temp % modulus;
        exponent >>= 1;
    }
    return result;
}

int main() {
    int base = 3;
    int exponent = 39;
    unsigned long long result;

    printf("Fast Exponentiation (Recursive): %llu\n", fastExponentiation(base, exponent));
    printf("Fast Exponentiation (Iterative): %llu\n", fastExponentiationIterative(base, exponent));
    printf("Fast Modular Exponentiation: %d\n", fastModularExponentiation(base, exponent, 1000000));
}
