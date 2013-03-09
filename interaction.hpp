#include "body.hpp"

class Interaction {

protected:

	Body* earth;
	Body* apple;

public:

	void registerBodies(Body* earth, Body* apple);

	virtual void actuate(Body &accelerationOfEarth, Body &accelerationOfApple, const double t) = 0;

	virtual double energy() = 0;

	virtual ~Interaction() = 0;
};
