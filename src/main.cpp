#include <iostream>

#include "gaussianesque.h"
#include "taylor_series_approximator.h"

using std::cout;

int main() {
    gaussianesque g(1, 5);
    taylor_series_approximator appr;

    // Keep in mind, the taylor series approximation of
    // a "gaussianesque" function will only be necessarily accurate
    // on the right half. However, a gaussianesque is symmetrical,
    // so the left half can be inferred from the right half. As
    // such, when collecting data, make sure to always use
    // the right half, and then flipping signs in case of finding
    // an integral in the left half.

    // Also consider using the trapezoid method for calculating integrals.
    // Keep in mind that this would be incredibly slow for any amount of
    // accuracy, especially as integrals have to be calculated within quite
    // a large range.

    // Make sure to only integrate within the interval of convergence, as well.
    // Otherwise, the accuracy will fault. Simply define a window of interest
    // within the interval of convergence, and consider that the entire
    // distribution (P(x outside of window) = 0). The interval of convergence
    // can be easily determined empirically, by simply testing values of g's approximation
    // against g itself until they are no longer accurate.

    polynomial *p = appr.approximate(g, 0, 20);

    cout << "p(0) = " << (*p)(0) << "\n";
    cout << "g(0) = " << g(0) << "\n";
    cout << "p(.1) = " << (*p)(.1) << "\n";
    cout << "g(.1) = " << g(.1) << "\n";
    cout << "p(.5) = " << (*p)(.5) << "\n";
    cout << "g(.5) = " << g(.5) << "\n";
    cout << "p(1) = " << (*p)(1) << "\n";
    cout << "g(1) = " << g(1) << "\n";
    cout << "p(5) = " << (*p)(5) << "\n";
    cout << "g(5) = " << g(5) << "\n";
    cout << "p(10) = " << (*p)(10) << "\n"; // Outside of interval of convergence
    cout << "g(10) = " << g(10) << "\n";
    cout << "p(100) = " << (*p)(100) << "\n";
    cout << "g(100) = " << g(100) << "\n";

    p->print();

    delete p;
    return 0;
}
