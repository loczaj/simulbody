#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include "../interaction.hpp"

class GravitationalInteraction: public Interaction {

private:
	double gammaM1M2;
	double factor = 0.0;

public:
	GravitationalInteraction(double gammaM1M2, sizeT earth, sizeT moon);

	virtual void apply(const Phase &phase, const double t) override;

	virtual double getEnergy(const Phase &phase) override;

	virtual ~GravitationalInteraction() override;
};


#endif // GRAVITY_HPP
