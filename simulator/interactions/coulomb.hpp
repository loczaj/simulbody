#ifndef COULOMB_HPP
#define COULOMB_HPP

#include "../interaction.hpp"

class CoulombInteraction: public Interaction {

private:
	double q1q2;

public:
	CoulombInteraction(double q1q2, sizeT earth, sizeT moon);

	virtual void apply(const Phase &phase, const double t) override;

	virtual double getEnergy(const Phase &phase) override;

	virtual ~CoulombInteraction() override;
};


#endif // COULOMB_HPP
