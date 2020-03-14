#include <stdexcept>
#include <exception>
#include <iostream>

#include "table_function.h"

using std::cout;

table_function::table_function() {
    table = NULL;
    intervals = 0;
}

table_function::table_function(int intervals) {
    table = new double[intervals];
    this->intervals = intervals;
}

double table_function::operator()(double x) {
    int index = x_to_index(x);
    if (index < 0 || index >= intervals) {
        throw std::out_of_range("Index out of bounds of approximation");
    }
    return table[index];
}

table_function::~table_function() {
    delete [] table;
}
