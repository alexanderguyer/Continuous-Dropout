#include <cstdlib>
#include <iostream>
#include "gaussianesque_distribution.h"
#include "taylor_series_approximator.h"

using std::cout;

gaussianesque_distribution::gaussianesque_distribution(gaussianesque *g, int upper_bound) {
    this->upper_bound = upper_bound;
    taylor_series_approximator appr;
    polynomial *p = appr.approximate(*g);
    approximated_integral = p->integrate();
    delete p;
    window_integral = 2 * (*approximated_integral)(upper_bound);
}

double gaussianesque_distribution::operator()() {
    // Generate a uniform random number within the window integral
    double desired_integral = (rand() % ((int) (window_integral * 1000))) / 1000.0;
    // The window integral is the area under the relevant part of the curve,
    // ignoring negatives. Subtract half of the window integral make the range between
    // -upper_integral (a.k.a. lower_integral) and upper_integral
    desired_integral -= (window_integral / 2.0);

    // Do a binary search to find the spot on the polynomial with this integral. It's
    // a monotonically increasing function, so binary search works well
    double event_value = 0;
    double delta = desired_integral;
    double shift = upper_bound / 2.0; // Starts in the middle (event_value = 0) and
    // ...shifts one quartile when ready
    double max_delta = 0.001 * window_integral;
    do {
        if (delta < 0) {
            event_value -= shift;
        } else if (delta > 0) {
            event_value += shift;
        }
        shift /= 2.0; // Adjust shift. Second iteration will shift one eighth, etc.
        delta = desired_integral - (*approximated_integral)(event_value);
    } while (delta > max_delta || delta < -max_delta);

    // The event value is the transformed random variable following the correct distribution
    return event_value / 100.0;
}
