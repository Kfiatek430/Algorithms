#include <iostream>
#include <cmath>
#include <list>
#include <vector>

using namespace std;

int main() {
    int multiplier = 2;
    const int maxLimit = static_cast<int>(multiplier * 1e6) % static_cast<int>(1e9); 
    cout << maxLimit << endl;

    vector<bool> sieve(maxLimit, true);
    cout << maxLimit << endl;

    sieve[0] = sieve[1] = false;

    list<int> primeNumbers;

    for (int i = 2; i < maxLimit; ++i) {
        if (sieve[i]) {
            primeNumbers.push_back(i);
            for (int j = i * 2; j < maxLimit; j += i) {
                sieve[j] = false;
            }
        }
    }

    for (const auto& prime : primeNumbers) {
        cout << prime << endl;
    }

    return 0;
}
