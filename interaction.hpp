#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "phase.hpp"

namespace simulbody {

class Interaction {

	friend class System;

private:

	identifier earth;
	identifier moon;

protected:

	// variables for calculation
	vector3D r;
	vector3D v;
	vector3D F;

	// methods for calculation
	void calculateR(const Phase &phase);
	void calculateV(const Phase &phase);

	void applyFOnMoon(const Phase &phase);
	void applyFOnEarth(const Phase &phase);

public:

	virtual void setBodies(identifier earth, identifier moon);

	virtual void apply(const Phase &phase, const double t) = 0;

	virtual double getEnergy(const Phase &phase) = 0;

	virtual ~Interaction();
};

} /* NAMESPACE SIMULBODY */

#endif // INTERACTION_HPP