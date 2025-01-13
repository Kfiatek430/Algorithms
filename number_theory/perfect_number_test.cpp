#include<iostream>
#include<cmath>
#include<set>

using namespace std;

int main() {
    int number = 496;
    set<int> divisors;
    divisors.insert(1);

    for (int i = 2; i <= number / 2; i++) {
        if (number % i == 0) divisors.insert(i);
    }

    int sumOfDivisors = 0;
    for (auto divisor : divisors) {
        sumOfDivisors += divisor;
    }

    if (sumOfDivisors == number) {
        cout << "The number is perfect";
    } else {
        cout << "The number is not perfect";
    }

    return 0;
}
