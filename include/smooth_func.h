#ifndef SMOOTH_H
#define SMOOTH_H

#include "differentiable_func.h"

class smooth_func : public differentiable_func {
    virtual differentiable_func *differentiate() = 0;
};

#endif
