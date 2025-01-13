#include<iostream>
#include<cmath>
#include<list>
#include <bits/stdc++.h>
#include<string.h>

using namespace std;

unsigned long long fastExponentiation(int base, int exponent) {
    if (exponent == 1) return base;
    if (exponent & 1)
        return base * fastExponentiation(base, exponent - 1);
    else {
        unsigned long long halfPower = fastExponentiation(base, exponent / 2);
        return halfPower * halfPower;
    }
}

int main() {
    int limit = 40;
    char sieve[limit];
    list<int> primes;
    list<int> powers;

    for (int i = 0; i < limit; sieve[i++] = 1) {}

    for (int i = 0; i < limit; i++) {
        if (i <= 1) sieve[i] = 0;
        else if (sieve[i]) {
            primes.push_back(i);
            for (int j = 0; j < limit; j += i) sieve[j] = 0;
        }
    }

    for (int i = 2; i < limit; i++) {
        powers.push_back(fastExponentiation(2, i) - 1);
    }

    list<int> mersennePrimes;
    for (auto prime : primes) {
        for (auto power : powers) {
            if (prime == power) mersennePrimes.push_back(prime);
        }
    }

    for (auto mersennePrime : mersennePrimes) {
        cout << mersennePrime << endl;
    }

    return 0;
}
