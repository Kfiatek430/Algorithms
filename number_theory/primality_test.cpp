#include<iostream>
#include<cmath>

using namespace std;

bool isPrime(int number) {
    if (number < 2) return false;
    int limit = sqrt(number);

    if (number % 2 == 0) return false;
    for (int i = 3; i <= limit; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}

int main() {
    int number = 13;
    if (isPrime(number))
        cout << "The number is prime";
    else
        cout << "The number is not prime";
}
