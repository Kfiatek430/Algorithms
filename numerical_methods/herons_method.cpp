#include<iostream>

using namespace std;

int main() {
    printf("Calculating square root of a number\n");
    float epsilon = 0.01;
    float number;
    cin >> number;

    float approximation = number;
    float divisor = 1;

    while ((approximation - divisor) > epsilon) {
        approximation = (approximation + divisor) / 2;
        divisor = number / approximation;
        printf("%f, %f \n", approximation, divisor);
    }

    printf("\nFinal approximation: %f, %f", approximation, divisor);
}
