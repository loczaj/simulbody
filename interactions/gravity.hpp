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

	virtual void apply(const Phase &x, Phase &dxdt, const double t) override {

		calculateRelativePositionR(x);

		factor = -gammaM1M2 / pow(r.abs(), 3);
		F = r;
		F *= factor;

		applyForceOnMoon(dxdt, F);
		applyForceOnEarth(dxdt, -F);
	}

	virtual double getEnergy(const Phase &phase) override {
		calculateRelativePositionR(phase);
		return -gammaM1M2 / r.abs();
	}

	virtual ~GravitationalInteraction() override {
	}
};

} /* NAMESPACE SIMULBODY */

#endif /* GRAVITY_HPP */
