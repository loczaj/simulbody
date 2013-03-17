#include "../interaction.hpp"

class CoulombInteraction: public Interaction {

private:
	double q1q2;

public:
	CoulombInteraction(double q1q2);

	virtual void affect(const double t);

	virtual double energy();

	virtual ~CoulombInteraction() = 0;
};
