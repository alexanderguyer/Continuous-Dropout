#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "smooth_func.h"

class polynomial : public smooth_func {
private:
    class term {
    private:
        double coefficient;
        double exponent;
    public:
        term(double, double);

        double get_coefficient();
        double get_exponent();
    };

    term **terms;
    int cap_terms; // Maximum amount of terms a polynomial can have
    int num_terms = 0; // Amount of terms a polynomial actually has
public:
    polynomial(int);
    ~polynomial();

    void print();

    void push_term(double, double);

    polynomial *differentiate();

    polynomial *integrate(); // Does not encode unknown constant
    polynomial *integrate(int); // Encodes supplied constant as its own term

    double operator()(double);
};

#endif
