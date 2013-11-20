#ifndef COULOMB_HPP
#define COULOMB_HPP

#include <math.h>
#include "../interaction.hpp"

namespace simulbody {

class CoulombInteraction: public Interaction {

private:
	double q1q2;
	double factor = 0.0;

public:
	CoulombInteraction(double q1q2, identifier earth, identifier moon) {
		this->q1q2 = q1q2;
		this->setBodies(earth, moon);
	}

	virtual void apply(const Phase &phase, const double t) override {

		calculateR(phase);

		factor = q1q2 / pow(r.abs(), 3);
		F = r;
		F *= factor;

		applyFOnMoon(phase);
		applyFOnEarth(phase);
	}

	virtual double getEnergy(const Phase &phase) override {
		calculateR(phase);
		return q1q2 / r.abs();
	}

	virtual ~CoulombInteraction() override {
	}
};

} /* NAMESPACE SIMULBODY */

#endif /* COULOMB_HPP */
