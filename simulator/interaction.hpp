#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "body.hpp"

class Interaction {

protected:

	Body* earth;
	Body* moon;

	// variables for calculation
	double rx, ry, rz;
	double vx, vy, vz;
	double Fx, Fy, Fz;
	double r, r2;
	double v, v2;
	double F;

	// methods for calculation
	void calculateRxyz();
	void calculateRxyzR2();
	void calculateRxyzR2R();
	void calculateVxyz();
	void calculateVxyzV2();
	void calculateVxyzV2V();

	void applyFxyzOnMoon();
	void applyFxyzOnEarth();

public:

	void registerBodies(Body* earth, Body* moon);

	virtual void apply(const double t) = 0;

	virtual double energy() = 0;

	virtual ~Interaction();
};

#endif // INTERACTION_HPP
