#include <cstdlib>
#include "gaussianesque_distribution.h"
#include "taylor_series_approximator.h"

#include <iostream>

using std::cout;

gaussianesque_distribution::gaussianesque_distribution(gaussianesque *g, double upper_bound, int intervals) {
    this->upper_bound = upper_bound;
    approximated_integral = new trapezoidal_integral_approximation(g, 0, upper_bound, intervals);
    window_integral = 2 * (*approximated_integral)(upper_bound);
}

double gaussianesque_distribution::operator()() {
    // Generate a uniform random number within the window integral
    double desired_integral = (rand() % ((int) (window_integral * 1000))) / 1000.0;
    // The window integral is the area under the relevant part of the curve,
    // ignoring negatives. Subtract half of the window integral to make the range between
    // -upper_integral (a.k.a. lower_integral) and upper_integral
    desired_integral -= (window_integral / 2.0);

    // Do a binary search to find the spot on the polynomial with this integral. It's
    // a monotonically increasing function, so binary search works well
    double event_value = 0;
    double delta = desired_integral;
    double shift = upper_bound / 2.0; // Starts in the middle (event_value = 0) and
    // ...shifts one quartile when ready
    double max_delta = 0.00001 * window_integral;
    double previous_delta;
    double diff;
    do {
        if (delta < 0) {
            event_value -= shift;
        } else if (delta > 0) {
            event_value += shift;
        }
        shift /= 2.0; // Adjust shift. Second iteration will shift one eighth, etc.
        previous_delta = delta;
        double curr_integral = event_value > 0 ? (*approximated_integral)(event_value) : -(*approximated_integral)(-event_value);
        delta = desired_integral - curr_integral;
        diff = delta - previous_delta;
        diff *= diff < 0 ? -1 : 1;
    } while (diff >= 0.00001);

    // The event value is the transformed random variable following the correct distribution
    return event_value;
}

gaussianesque_distribution::~gaussianesque_distribution() {
    delete approximated_integral;
}
