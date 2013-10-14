#include "../interaction.hpp"

class CoulombInteraction: public Interaction {

private:
	double q1q2;

public:
	CoulombInteraction(double q1q2);

	virtual void apply(const double t);

	virtual double getEnergy();

	virtual ~CoulombInteraction();
};
