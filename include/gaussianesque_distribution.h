#ifndef GAUSSIANESQUE_DISTRIBUTION_H
#define GAUSSIANESQUE_DISTRIBUTION_H

#include "continuous_distribution.h"
#include "trapezoidal_integral_approximation.h"
#include "gaussianesque.h"

// This class represents a continuous probability distribution
// whose PDF is a gaussianesque function (see gaussianesque.(h|cpp)).
// The gaussianesque PDF is converted into a distribution through
// a probability integral transform.

// A probability integral transform involves the following steps:
// Find the integral within a window of relevance for a PDF (let's
// define the window by horizontal bounds a and b). In other words,
// determine CDF(b) - CDF(a). Let's call this
// integral from a to b of the PDF "c". Next, generate a uniform real
// random number d between 0 and c (using rand(), etc). Lastly, find
// the value e for which CDF(e) - CDF(a) = d. e represents a real
// random number from the distribution described by the PDF.

// Think of the 68% - 95% - 99.7% rule. A majority of the area under a normal distribution
// is within a single standard deviation of the mean. Almost all of it is within 3 standard
// deviations within the mean. An essentially negligible amount is beyond 4 standard deviations
// from the mean. We can use this knowledge to do a probability integral transform: if we
// randomly generate an integral (uniformly) between 0 and 1 (which includes all possible integrals for
// a normal distribution), then there is a 68% chance it will be between .16 and .84, which represents
// the middle +/- standard deviation. If we then figure out the right bound which
// produces that integral, we'll have the x location / random point from the distribution which is within
// +/- 1 standard deviation from the middle. In other words, using this method, there is a 68% chance of
// getting a value within 1 standard deviation.

// However, the integral of our distribution function / PDF does not have to be 1.
// Sure, it technically isn't a PDF unless it is 1. However, in order to make it 1,
// you simply have to normalize it by dividing by its integral. We can actually cut
// that step out entirely, however. When we're randomly generating an integral, instead
// of generating an integral between 0 and 1, we simply generate an integral between 0 and
// c, where c is the maximum relevant integral. For example, if we choose a and b as our
// bounds for our window of relevance, then c is the integral from a to b of our distribution function.
// If our distribution function is 2 * (a normal distribution), then 68% of the area under
// the curve will still be between +/- 1 standard deviation. Sure, there's twice as much
// area there as there normally would be, since we've dilated the normal distribution, but
// the proportion is the same, so the transformation holds.

class gaussianesque_distribution : public continuous_distribution {
private:
	static const int DEFAULT_INTERVALS = 1000;
	trapezoidal_integral_approximation* approximated_integral; // Used to approximate the probability
	// integral transform, since a gaussianesque is not integrable by elementary
	// means
	int upper_bound;
	double window_integral;
public:
	gaussianesque_distribution(gaussianesque *g, double upper_bound, int intervals = DEFAULT_INTERVALS); // Accepts a gaussianesque, approximates
	// it to a polynomial with a taylor series, and does probability integral transformations
	// on it to generate values following the normalized gaussianesque as the PDF.

	virtual double operator()(); // To be defined

	~gaussianesque_distribution();
};

#endif
