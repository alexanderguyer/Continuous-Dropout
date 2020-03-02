/**

	MEAN SUM OF ERRORS
	Created by Alexander Guyer

*/

#ifndef CROSS_ENTROPY_H
#define CROSS_ENTROPY_H

#include "loss_function.h"

class cross_entropy : public loss_function{
	public:
		virtual double operator()(double, double, double) const;
		virtual loss_function *clone() const;
};

#endif
