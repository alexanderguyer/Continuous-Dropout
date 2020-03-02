#include <cmath>
#include "cross_entropy.h"

double cross_entropy::operator()(double input, double activation, double desired_activation) const{
	if (abs(1 - desired_activation) <= 0.01) {
		return -(input / activation);
	} else {
		return input / (1 - activation);
	}
}

loss_function *cross_entropy::clone() const{
	return new cross_entropy;
}
