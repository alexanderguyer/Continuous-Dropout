#ifndef GAUSSIANESQUE_H
#define GAUSSIANESQUE_H

#include "math.h"

class gaussianesque {
private:
    class parameter_set {
    private:
        double alpha, beta;
    public:
        parameter_set(double alpha, double beta);

        double get_alpha();
        double get_beta();
    };

    // Terms are of the form c * x^k * e^(-abs(x/beta)^alpha)
    // The parameters "c" and "k" change as gaussianesque functions are differentiated
    class term {
    private:
        double coefficient, exponent;
    public:
        term(double coefficient, double exponent);

        double get_coefficient();
        double get_exponent();
    };

    parameter_set *parameters;
    term **terms;
    int num_terms;
    bool originating;

    // For constructing a gaussianesque as a derivative of another gaussianesque
    gaussianesque(parameter_set *originating_parameters, term **terms, int num_terms);
public:
    gaussianesque(double alpha, double beta);

    gaussianesque* differentiate();

    ~gaussianesque();
};

#endif
