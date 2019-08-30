#include "gaussianesque.h"

gaussianesque::parameter_set::parameter_set(double alpha, double beta) {
   this->alpha = alpha;
   this->beta = beta;
}

double gaussianesque::parameter_set::get_alpha() {
    return alpha;
}

double gaussianesque::parameter_set::get_beta() {
    return beta;
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

gaussianesque::gaussianesque(parameter_set *originating_parameters, term **terms, int num_terms) {
    this->parameters = originating_parameters;
    this->terms = terms;
    this->num_terms = num_terms;
    originating = false;
}

gaussianesque::gaussianesque(double alpha, double beta) {
    parameters = new parameter_set(alpha, beta);
    num_terms = 1; // Originating function has only a single term
    terms = new term*[num_terms];
    terms[0] = new term(1, 0);

    // Used to destroy the parameter_set, which is shared between the
    // original gaussian function and its derivatives
    originating = true;
}

gaussianesque *gaussianesque::differentiate() {
    // If "this" is the originating function, its derivative
    // will also only have one term. Otherwise, the number of terms will double.

    term **terms;
    int num_terms;
    if (originating) {
        num_terms = 1;
        terms = new term*[num_terms];
        terms[0] = new term(-(parameters->get_alpha()) / pow(parameters->get_beta(), parameters->get_alpha()),
                         parameters->get_alpha() - 1);
    } else {
        num_terms = this->num_terms * 2;
        terms = new term*[num_terms];

        // Each term differentiates into two more terms via the product rule
        for (int i = 0; i < this->num_terms; i++) {
            terms[2 * i] = new term(this->terms[i]->get_coefficient() * this->terms[i]->get_exponent(),
                                    this->terms[i]->get_exponent() - 1);

            terms[2 * i + 1] = new term(this->terms[i]->get_coefficient() * -(parameters->get_alpha()) / pow(parameters->get_beta(), parameters->get_alpha()),
                                        parameters->get_alpha() - 1 + this->terms[i]->get_coefficient());
        }
    }

    return new gaussianesque(parameters, terms, num_terms);
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
