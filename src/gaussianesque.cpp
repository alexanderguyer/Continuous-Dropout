#include <stdexcept>
#include "gaussianesque.h"

gaussianesque::parameter_set::parameter_set(double alpha, double beta) {
   this->alpha = alpha;
   this->beta = beta;
   neg_recip_beta_to_alpha = -1.0/pow(beta, alpha);
}

double gaussianesque::parameter_set::get_alpha() {
    return alpha;
}

double gaussianesque::parameter_set::get_beta() {
    return beta;
}

double gaussianesque::parameter_set::get_neg_recip_beta_to_alpha() {
    return neg_recip_beta_to_alpha;
}

gaussianesque::term::term(double coefficient, double exponent) {
    this->coefficient = coefficient; // Represents "c" in above notation
    this->exponent = exponent; // Represents "k" in above notation
}

double gaussianesque::term::get_coefficient() {
    return coefficient;
}

double gaussianesque::term::get_exponent() {
    return exponent;
}

gaussianesque::gaussianesque(parameter_set *originating_parameters, int cap_terms) {
    this->parameters = originating_parameters;
    this->cap_terms = cap_terms;
    originating = false;
}

gaussianesque::gaussianesque(double alpha, double beta) {
    parameters = new parameter_set(alpha, beta);
    cap_terms = 1;
    num_terms = 1; // Originating function has only a single term
    terms = new term*[cap_terms];
    terms[0] = new term(1, 0);

    // Used to destroy the parameter_set, which is shared between the
    // original gaussian function and its derivatives
    originating = true;
}

gaussianesque *gaussianesque::differentiate() {
    // If "this" is the originating function, its derivative
    // will also only have one term. Otherwise, the number of terms will double.

    gaussianesque *res;
    if (originating) {
        res = new gaussianesque(parameters, 1);
        res->push_term(parameters->get_alpha() * parameters->get_neg_recip_beta_to_alpha(),
                       parameters->get_alpha() - 1);
    } else {
        res = new gaussianesque(parameters, num_terms * 2);

        // Each term differentiates into two more terms via the product rule
        for (int i = 0; i < this->num_terms; i++) {
            res->push_term(this->terms[i]->get_coefficient() * this->terms[i]->get_exponent(),
                           this->terms[i]->get_exponent() - 1);

            res->push_term(parameters->get_neg_recip_beta_to_alpha() * parameters->get_alpha() * terms[i]->get_coefficient(),
                           parameters->get_alpha() - 1 + this->terms[i]->get_exponent());
        }
    }

    return res;
}

gaussianesque::~gaussianesque() {
    for (int i = 0; i < num_terms; i++) {
        delete terms[i];
    }
    delete [] terms;

    if (originating) {
        delete parameters;
    }
}

void gaussianesque::push_term(double coefficient, double exponent) {
    // If num_terms exceeds cap_terms specified during construction,
    // throw an exception
    if (num_terms >= cap_terms) {
        throw std::out_of_range("Exceeded term limit specified during construction.");
    }

    // Otherwise, push it and keep track of how many terms have been pushed
    terms[num_terms] = new term(coefficient, exponent);
    num_terms++;
}

double gaussianesque::operator()(double x) {
    // To make this a function object, implement the ()(double) operator.

    // Calculate each term, and add them up.
    double sum = 0;
    for (int i = 0; i < num_terms; i++) {
        // Each term is of the form cx^k*E(x), where E(x) = e^((-1/beta^alpha) * x^alpha)
        sum += terms[i]->get_coefficient() * pow(x, terms[i]->get_exponent()) * exp(parameters->get_neg_recip_beta_to_alpha()*pow(x, parameters->get_alpha()));
    }
    return sum;
}
