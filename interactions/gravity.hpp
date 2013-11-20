#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <math.h>
#include "../interaction.hpp"

namespace simulbody {

class GravitationalInteraction: public Interaction {

private:
	double gammaM1M2;
	double factor = 0.0;

public:
	GravitationalInteraction(double gammaM1M2, identifier earth, identifier moon) {
		this->gammaM1M2 = gammaM1M2;
		this->setBodies(earth, moon);
	}

	virtual void apply(const Phase &phase, const double t) override {

		calculateR(phase);

		factor = -gammaM1M2 / pow(r.abs(), 3);
		F = r;
		F *= factor;

		applyFOnMoon(phase);
		applyFOnEarth(phase);
	}

	virtual double getEnergy(const Phase &phase) override {
		calculateR(phase);
		return -gammaM1M2 / r.abs();
	}

	virtual ~GravitationalInteraction() override {
	}
};

} /* NAMESPACE SIMULBODY */

#endif /* GRAVITY_HPP */
