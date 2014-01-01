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

	virtual void apply(const Phase &x, Phase &dxdt, const double t) override {

		calculateRelativePositionR(x);

		factor = q1q2 / pow(r.abs(), 3);
		F = r;
		F *= factor;

		applyForceOnMoon(dxdt, F);
		applyForceOnEarth(dxdt, -F);
	}

	virtual double getEnergy(const Phase &phase) override {
		calculateRelativePositionR(phase);
		return q1q2 / r.abs();
	}

	virtual ~CoulombInteraction() override {
	}
};

} /* NAMESPACE SIMULBODY */

#endif /* COULOMB_HPP */
