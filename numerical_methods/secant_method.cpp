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

    int max_iterations = 100, iteration = 0;
    
    while (fabs(lower_limit - upper_limit) >= tolerance && iteration < max_iterations) {
        root = lower_limit - function(lower_limit) * (upper_limit - lower_limit) / (function(upper_limit) - function(lower_limit));
        upper_limit = lower_limit;
        lower_limit = root;
        iteration++;
    }
    
    printf("%f, %f", root, function(root));
}
