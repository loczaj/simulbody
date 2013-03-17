#include "body.hpp"

class Interaction {

protected:

	Body* earth;
	Body* apple;

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

	void affectFxyzOnApple();
	void affectFxyzOnEarth();

public:

	virtual void registerBodies(Body* earth, Body* apple);

	virtual void affect(const double t) = 0;

	virtual double energy() = 0;

	virtual ~Interaction() = 0;
};
