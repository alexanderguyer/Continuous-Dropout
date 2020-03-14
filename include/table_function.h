#ifndef TABLE_FUNCTION_H
#define TABLE_FUNCTION_H

#include "real_func.h"

/* A table function is a function defined by a table
   relating x values to y values. When an x value
   is given which is not a key in the table, the closest
   key is used. It is an approximated representation of a
   function, useful when other approximations like taylor
   series diverge too early or don't provide the desired
   accuracy within a bounded context
*/

class table_function : public real_func {
protected:
    double *table;
    int intervals;

    virtual int x_to_index(double x) = 0;
public:
    table_function();
    table_function(int intervals);

    double operator()(double x);

    ~table_function();
};

#endif
