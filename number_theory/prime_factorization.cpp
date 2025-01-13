#include<iostream>
#include<cmath>

using namespace std;

int main() {
    int number = 100;
    int divisor = 2;

    while (number > 1) {
        if (number % divisor == 0) {
            cout << divisor << "\n";
            number = floor(number / divisor);
        } else {
            divisor++;
        }
    }
}
