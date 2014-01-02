#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "phase.hpp"

namespace simulbody {

class Interaction {

	friend class System;
	friend class InteractionPrintField;

protected:

	// bodies
	identifier earth;
	identifier moon;

	// variables for calculation
	vector3D r;
	vector3D v;
	vector3D F;
	vector3D vcoll;

	// methods for calculation
	void calculateRelativePositionR(const Phase &phase);
	void calculateRelativeVelocityV(const Phase &phase);

	void applyForceOnMoon(Phase &dxdt, const vector3D &force);
	void applyForceOnEarth(Phase &dxdt, const vector3D &force);

	void addCollateralVelocityOnMoon(Phase &dxdt, const vector3D &velocity);
	void addCollateralVelocityOnEarth(Phase &dxdt, const vector3D &velocity);

public:

	virtual void setBodies(identifier earth, identifier moon);

	virtual void apply(const Phase &x, Phase &dxdt, const double t) = 0;

	virtual double getEnergy(const Phase &phase) = 0;

	virtual ~Interaction();
};

} /* NAMESPACE SIMULBODY */

#endif // INTERACTION_HPP
