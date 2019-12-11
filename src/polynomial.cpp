#include <cmath>
#include <stdexcept>
#include <iostream>

#include "polynomial.h"

using std::cout;

polynomial::term::term(double coefficient, double exponent) {
    this->coefficient = coefficient;
    this->exponent = exponent;
}

double polynomial::term::get_coefficient() {
    return coefficient;
}

double polynomial::term::get_exponent() {
    return exponent;
}

polynomial::polynomial(int cap_terms) {
    this->cap_terms = cap_terms;
    terms = new term*[cap_terms];
}

polynomial::~polynomial() {
    for (int i = 0; i < num_terms; i++) {
        delete terms[i];
    }
    delete [] terms;
}

void polynomial::push_term(double coefficient, double exponent) {
    // If the term limit is exceeded, throw an exception
    if (num_terms >= cap_terms) {
        throw std::out_of_range("Term limit specified construction exceeded");
    }

    // Otherwise, push the term on and keep track of how many terms have been pushed
    terms[num_terms] = new term(coefficient, exponent);
    num_terms++;
}

double polynomial::operator()(double x) {
    double sum = 0;

    // To call a polynomial, calculate all terms and return the sum
    for (int i = 0; i < num_terms; i++) {
        sum += terms[i]->get_coefficient() * pow(x, terms[i]->get_exponent());
    }

    return sum;
}

polynomial *polynomial::differentiate() {
    // Differentiate each term and push it into a new polynomial
    polynomial *res = new polynomial(num_terms);
    for (int i = 0; i < num_terms; i++) {
        // Each term is cx^k. Derivative of a term is ckx^(k-1), or c => ck, k => k - 1. Don't add a term if the exponent is zero
        if (terms[i]->get_exponent() == 0) {
            continue; // This is a constant. It should not get differentiated into an exponent of -1. Just continue.
        }

        res->push_term(terms[i]->get_coefficient() * terms[i]->get_exponent(), terms[i]->get_exponent() - 1);
    }

    // Return the new polynomial
    return res;
}

polynomial *polynomial::integrate() {
    // Integrate each term and push it into a new polynomial. Does not encode unknown constant.
    polynomial *res = new polynomial(num_terms);
    for (int i = 0; i < num_terms; i++) {
        // Each term is cx^k. Integral of a term is (c/(k+1))x^(k+1), or c => c/(k+1), k => k + 1.
        res->push_term(terms[i]->get_coefficient() / (terms[i]->get_exponent() + 1), terms[i]->get_exponent() + 1);
    }

    // Return the new polynomial
    return res;
}

polynomial *polynomial::integrate(int constant) {
    // Integrate each term and push it into a new polynomial. Encodes constant as an extra term
    polynomial *res = new polynomial(num_terms + 1); // + 1 for constant
    for (int i = 0; i < num_terms; i++) {
        // Each term is cx^k. Integral of a term is (c/(k+1))x^(k+1), or c => c/(k+1), k => k + 1.
        res->push_term(terms[i]->get_coefficient() / (terms[i]->get_exponent() + 1), terms[i]->get_exponent() + 1);
    }
    res->push_term(constant, 0); // constant * x^0 = constant * 1 = constant

    // Return the new polynomial
    return res;
}

void polynomial::print() {
    for (int i = 0; i < num_terms; i++) {
        if (i > 0) {
            cout << " + ";
        }
        cout << terms[i]->get_coefficient() << "x^" << terms[i]->get_exponent();
    }
    cout << "\n";
}
