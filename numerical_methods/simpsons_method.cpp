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
    double interval_width = fabs(upper_limit - lower_limit) / num_intervals;

    int sum_even = 0;
    int sum_odd = 0;
    
    for (int i = 1; i <= num_intervals; i++) {
        sum_odd += function(lower_limit + i * interval_width - interval_width / 2);
        if (i < num_intervals) sum_even += function(lower_limit + i * interval_width);
    }

    result = interval_width / 6 * (function(lower_limit) + function(upper_limit) + 2 * sum_even + 4 * sum_odd);
    printf("%f", result);
}
