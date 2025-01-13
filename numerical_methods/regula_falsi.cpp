#include<iostream>
#include<cmath>
using namespace std;

double function(double x) {
    return pow(x - 5, 3);
}

int main() {
    double lower_limit = -100;
    double upper_limit = 100;
    double root;
    double tolerance = 1E-5;

    do {
        root = lower_limit - function(lower_limit) * (upper_limit - lower_limit) / (function(upper_limit) - function(lower_limit));
        if (function(lower_limit) * function(root) < 0) {
            upper_limit = root;
        } else {
            lower_limit = root;
        }
    } while (fabs(function(root)) >= tolerance);
    
    printf("%f, %f", root, function(root));
}