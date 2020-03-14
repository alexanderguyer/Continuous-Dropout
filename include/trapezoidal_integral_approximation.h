#ifndef TRAPEZOIDAL_INTEGRAL_APPROXIMATION_H
#define TRAPEZOIDAL_INTEGRAL_APPROXIMATION_H

#include "table_function.h"

class trapezoidal_integral_approximation : public table_function {
private:
    double lower_bound;
    double upper_bound;
protected:
    virtual int x_to_index(double x);
public:
    trapezoidal_integral_approximation(real_func *, double lower_bound, double upper_bound, int intervals);
};

#endif
