#include "trapezoidal_integral_approximation.h"
#include <cmath>
#include <iostream>

using std::cout;

trapezoidal_integral_approximation::trapezoidal_integral_approximation(real_func *r, double lower_bound, double upper_bound, int intervals) : table_function(intervals) {
    this->lower_bound = lower_bound;
    this->upper_bound = upper_bound;
    double interval_width = (upper_bound - lower_bound) / intervals;
    table[0] = 0;
    double previous_x = 0;
    double previous_y = (*r)(0);
    double integral = 0;
    for (int i = 1; i < intervals; i++) {
        double x = lower_bound + (i * interval_width);
        double y = (*r)(x);
        // Construct area of trapezoid by breaking it into a rectangle plus
        // a triangle
        double smaller_y = y < previous_y ? y : previous_y;
        double rectangle_area = smaller_y * interval_width;
        double triangle_area = abs(y - previous_y) * interval_width / 2.0;
        integral += rectangle_area + triangle_area;
        table[i] = integral;
        previous_x = x;
        previous_y = y;
    }
}

int trapezoidal_integral_approximation::x_to_index(double x) {
    double interval_width = (upper_bound - lower_bound) / intervals;
    int interval = (x - lower_bound) / interval_width;
    if (interval == intervals) {
        interval--;
    }

    return interval;
}
