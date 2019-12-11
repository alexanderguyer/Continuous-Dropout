#ifndef GAUSSIANESQUE_H
#define GAUSSIANESQUE_H

#include <cmath>
#include "differentiable_func.h"
#include "smooth_func.h"

class gaussianesque : public smooth_func {
private:
    class parameter_set {
    private:
        double alpha, beta, neg_recip_beta_to_alpha;
    public:
        parameter_set(double alpha, double beta);

        double get_alpha();
        double get_beta();
        double get_neg_recip_beta_to_alpha();
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
    int cap_terms;
    int num_terms = 0;
    bool originating;

    // For constructing a gaussianesque as a derivative of another gaussianesque
    gaussianesque(parameter_set *originating_parameters, int cap_terms);
public:
    gaussianesque(double alpha, double beta);

    gaussianesque *differentiate();

    ~gaussianesque();

    void print();

    void push_term(double coefficient, double exponent);

    double operator()(double);
};

#endif
