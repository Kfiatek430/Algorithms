#include<iostream>
#include<cmath>
using namespace std;

#define roundToPrecision(value, precision) (round(value * pow(10, precision)) / pow(10, precision))

double function(double x) {
    return pow(x - 5, 3);
}

double bisection(double lower, double upper, double tolerance) {
    double midpoint = (lower + upper) / 2;

    if (abs(function(lower) - function(upper)) < tolerance) 
        return midpoint;

    if (function(lower) * function(midpoint) < 0) 
        upper = midpoint;
    else 
        lower = midpoint;

    return bisection(lower, upper, tolerance);
}

int main() {
    printf("Starting...\n");

    double lowerLimit = -1e10;
    double upperLimit = 1e10;
    double tolerance = 0.01;
    double root = 0;

    while (abs(function(lowerLimit) - function(upperLimit)) > tolerance) {
        printf("Processing...\n");

        root = (lowerLimit + upperLimit) / 2;

        if (function(root) * function(lowerLimit) < 0) {
            upperLimit = root;
        } else {
            lowerLimit = root;
        }

        printf("Current root approximation: %.10f %.10f \n", root, function(root));
    }

    root = roundToPrecision((lowerLimit + upperLimit) / 2, 5);
    double functionAtRoot = roundToPrecision(function(root), 5);

    printf("Final result: %.10f %.10f \n", root, functionAtRoot);

    cout << "Bisection method result: " << bisection(-1e10, 1e10, tolerance) << endl;
}
