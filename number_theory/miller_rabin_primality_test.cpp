#include <iostream>
#include <cmath>

using namespace std;

int gcd(int x, int y) {
    int remainder;
    while (y != 0) {
        remainder = x % y;
        x = y;
        y = remainder;
    }
    return x;
}

int modPow(int base, unsigned int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = static_cast<long long>(result % modulus) * static_cast<long long>(base % modulus) % modulus;
        }
        long long temp = base % modulus;
        temp *= temp;
        base = temp % modulus;
        exponent >>= 1;
    }
    return result;
}

bool isPrime(int number) {
    for (int i = 0; i < 20; i++) {
        int randomBase = rand() % (number - 2) + 2;
        cout << "Random base: " << randomBase << endl;

        if (gcd(number, randomBase) != 1 || modPow(randomBase, number - 1, number) != 1) {
            cout << "GCD(number, base) = " << gcd(number, randomBase) << " modPow(base, number-1, number) = " << modPow(randomBase, number - 1, number) << endl;
            return false;
        }
    }
    return true;
}

int main() {
    int numberToCheck = 97;
    if (isPrime(numberToCheck)) {
        cout << "The number is prime." << endl;
    } else {
        cout << "The number is not prime." << endl;
    }

    return 0;
}
