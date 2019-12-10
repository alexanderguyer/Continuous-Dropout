#include <iostream>

#include "gaussianesque.h"
#include "taylor_series_approximator.h"

using std::cout;

int main() {
    gaussianesque g(2, 1);
    taylor_series_approximator appr;
    /*
    polynomial p1(3);
    p1.push_term(1, 0);
    p1.push_term(2, 1);
    p1.push_term(3, 2);
    */

    // KEEP IN MIND, we have removed the absolute value from the form of the gaussianesque, because otherwise
    // the taylor series is VERY inaccurate. This is to be expected, as the derivative is calculated using
    // the right side of the function, which only extends to the left side if alpha is even (such as x^2).
    // Since odd alpha values lead to assymetric functions, the absolute value corrects this, but it also
    // throws off the higher order derivatives, making the taylor series fail.

    // TODO Consider approximating integrals by the trapezoid method instead of through a taylor approximation.
    // TODO In fact, just do it both ways, and see which performs better.

    polynomial *p = appr.approximate(g, 0, 5);
    cout << "p(0) = " << (*p)(0) << "\n";
    cout << "g(0) = " << g(0) << "\n";
    cout << "p(.1) = " << (*p)(.1) << "\n";
    cout << "g(.1) = " << g(.1) << "\n";
    cout << "p(.5) = " << (*p)(.5) << "\n";
    cout << "g(.5) = " << g(.5) << "\n";
    cout << "p(1) = " << (*p)(1) << "\n";
    cout << "g(1) = " << g(1) << "\n";
    cout << "p(5) = " << (*p)(.5) << "\n";
    cout << "g(5) = " << g(.5) << "\n";
    cout << "p(10) = " << (*p)(1) << "\n";
    cout << "g(10) = " << g(1) << "\n";

    delete p;
    return 0;
}
