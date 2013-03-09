#include <vector>

#include "body.hpp"

typedef std::vector<double> state_type;

class Interaction {

protected:

	Body* earth;
	Body* apple;

public:

	void registerBodies(Body* earth, Body* apple);

	virtual void actuate(Body &accelerationOfEarth, Body &accelerationOfApple, const double t) = 0;

	virtual double energy();

	virtual ~Interaction();
};

class Gravity: public Interaction {

public:

	void atuate(Body &accelerationOfEarth, Body &accelerationOfApple, const double t);

	double energy();
};
