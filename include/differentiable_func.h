#ifndef DIFFERENTIABLE_FUNC_H
#define DIFFERENTIABLE_FUNC_H

#include "real_func.h"

class differentiable_func : public real_func {
public:
    virtual real_func *differentiate() = 0;
};

#endif
