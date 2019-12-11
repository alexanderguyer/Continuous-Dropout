#include <cstdlib>
#include <iostream>

#include "taylor_series_approximator.h"

const int taylor_series_approximator::default_term_count = 10;

polynomial *taylor_series_approximator::approximate(smooth_func &s) const {
    return approximate(s, 0, taylor_series_approximator::default_term_count); // Maclaurin series with default term count when no "a" value is given
}

polynomial *taylor_series_approximator::approximate(smooth_func &s, const int a, const int term_count) const {
    polynomial *res = new polynomial(term_count);
    smooth_func *derivative = NULL; // The current relevant derivative
    double factorial = 1; // The current relevant factorial
    double constant = 0; // The constant is affected by each iteration in the taylor series, so compute it over time.

    // If there's more than one term, compute the first derivative; we'll need it
    if (term_count > 1) {
        derivative = s.differentiate();
    }

    for (int i = 0; i < term_count; i++) {
        // Each term is the ith derivative of f evaluated at a, divided by the factorial of i, multiplied by (x-a)^i
        if (i > 0) {
            // In this case, we use the i-1th derivative of s. Exponent is i.
            double coefficient = (*derivative)(a) / factorial;
            res->push_term(coefficient, i);
            // Also, since each instance of the taylor series is coeffient * (x - a), each instance contributes
            // to the constant term by coefficient * (-a)
            constant -= a * coefficient;

            // Compute the next relevant factorial and derivative, if necessary
            if (i < term_count - 1) {
                factorial *= (i + 1);
                smooth_func *next_derivative = derivative->differentiate();
                delete derivative;
                derivative = next_derivative;
            }
        } else {
            // In this case, we use s to add to the constant
            constant += s(a);
        }
    }


    // Add the computed constant, using 0 as the exponent
    res->push_term(constant, 0);

    // Free derivative. Freeing NULL is safe.
    delete derivative;

    // Return the new polynomial
    return res;
}
