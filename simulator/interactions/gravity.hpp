#include "../interaction.hpp"

class GravitationalInteraction: public Interaction {

private:
	double gamma;
	double gammaM1M2;

public:
	GravitationalInteraction(double gamma, Body* earth, Body* moon);

	virtual void setBodies(Body* earth, Body* moon);

	virtual void apply(const double t);

	virtual double getEnergy();

	virtual ~GravitationalInteraction();
};
