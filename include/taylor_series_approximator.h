#ifndef TAYLOR_SERIES_APPROXIMATOR
#define TAYLOR_SERIES_APPROXIMATOR

#include "smooth_func.h"
#include "polynomial.h"

class taylor_series_approximator {
public:
    static const int default_term_count;

    virtual polynomial *approximate(smooth_func &) const;
    polynomial *approximate(smooth_func &, const int, const int) const;
};

#endif
