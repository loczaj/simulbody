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

		calculateRelativePosition(x);

		factor = -gammaM1M2 / pow(relativePosition.abs(), 3);
		actingForce = relativePosition;
		actingForce *= factor;

		applyForceOnMoon(dxdt, actingForce);
		applyForceOnEarth(dxdt, -actingForce);
	}

	virtual double getEnergy(const Phase &phase) override {
		calculateRelativePosition(phase);
		return -gammaM1M2 / relativePosition.abs();
	}

	virtual ~GravitationalInteraction() override {
	}
};

} /* NAMESPACE SIMULBODY */

#endif /* GRAVITY_HPP */
