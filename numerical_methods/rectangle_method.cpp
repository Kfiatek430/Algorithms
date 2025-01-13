#include<iostream>
#include<cmath>

using namespace std;

double function(double x) {
    return 2 * x;
}

int main() {
    double lower_limit = 0;
    double upper_limit = 5;
    int num_intervals = 1000;
    double result = 0;

    for (int i = 0; i < num_intervals; i++) {
        double interval_width = fabs((upper_limit - lower_limit)) / num_intervals;
        double area = interval_width * fabs(function(lower_limit + i * interval_width));
        result += area;
    }

    printf("%f", result);
}