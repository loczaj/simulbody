#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include <stddef.h>

class Phase;

class Interaction {

private:

	size_t earth;
	size_t moon;

protected:

	// variables for calculation
	double rx, ry, rz;
	double vx, vy, vz;
	double Fx, Fy, Fz;
	double r, r2;
	double v, v2;
	double F;

	// methods for calculation
	void calculateRxyz(const Phase &phase);
	void calculateRxyzR2(const Phase &phase);
	void calculateRxyzR2R(const Phase &phase);
	void calculateVxyz(const Phase &phase);
	void calculateVxyzV2(const Phase &phase);
	void calculateVxyzV2V(const Phase &phase);

	void applyFxyzOnMoon(const Phase &phase);
	void applyFxyzOnEarth(const Phase &phase);

public:

	virtual void setBodies(size_t earth, size_t moon);

	virtual void apply(const Phase &phase, const double t) = 0;

	virtual double getEnergy(const Phase &phase) = 0;

	virtual ~Interaction();
};

#endif // INTERACTION_HPP
