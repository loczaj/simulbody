#include "../interaction.hpp"

class CoulombInteraction: public Interaction {

private:
	double q1q2;

public:
	CoulombInteraction(double q1q2, Body* earth, Body* moon);

	virtual void apply(const double t) override;

	virtual double getEnergy() override;

	virtual ~CoulombInteraction() override;
};
