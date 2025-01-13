#include<iostream>
#include<cmath>
using namespace std;

double function(double x) {
    return pow(x, 3) + 3 * pow(x, 2) + 1;
}

double functionDerivative(double x) {
    return 6 * x + 3 * pow(x, 2);
}

int main() {
    double lowerBound = -5;
    double upperBound = 2;
    double root;
    double epsilon = 1E-5;
    int iterationCount = 0;

    do {
        root = upperBound - (function(upperBound) / functionDerivative(upperBound));
        upperBound = lowerBound;
        lowerBound = root;
        printf("Current approximation: %f\n", root);
        iterationCount++;
    } while (fabs(lowerBound - upperBound) >= epsilon);
    
    printf("End of process\n");
    printf("Final root approximation: %f, f(root) = %f\n", root, function(root));

    return 0;
}
