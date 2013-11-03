#include "../interaction.hpp"

class GravitationalInteraction: public Interaction {

private:
	double gammaM1M2;

public:
	GravitationalInteraction(double gammaM1M2, size_t earth, size_t moon);

	virtual void apply(const Phase &phase, const double t) override;

	virtual double getEnergy(const Phase &phase) override;

	virtual ~GravitationalInteraction() override;
};
