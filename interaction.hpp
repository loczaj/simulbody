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

	// masses
	double earthMass;
	double moonMass;
	double reducedMass;

	// variables for calculation
	vector3D relativePosition;
	vector3D relativeVelocity;
	vector3D actingForce;
	vector3D actingVelocity;

	// methods for calculation
	void calculateRelativePosition(const Phase &phase);
	void calculateRelativeVelocity(const Phase &phase);

	void applyForceOnMoon(Phase &dxdt, const vector3D &force);
	void applyForceOnEarth(Phase &dxdt, const vector3D &force);

	void addVelocityOnMoon(Phase &dxdt, const vector3D &velocity);
	void addVelocityOnEarth(Phase &dxdt, const vector3D &velocity);

	virtual void setBodies(identifier earth, identifier moon);
	virtual void setBodyMasses(double earthMass, double moonMass);

	virtual void apply(const Phase &x, Phase &dxdt, const double t) = 0;

public:

	virtual double getEnergy(const Phase &phase) = 0;
	virtual double getDistance(const Phase &phase);

	virtual ~Interaction();
};

} /* NAMESPACE SIMULBODY */

#endif // INTERACTION_HPP
