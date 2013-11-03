#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>

#include "interaction.hpp"
#include "phase.hpp"

class System {

private:

	std::vector<Interaction*> interactions;
	// TODO Add fields

public:

	Phase phase;

	void addInteraction(Interaction *interaction);

	double getEnergy();

	void derive(const Phase &x, Phase &dxdt, const double t) const;

	System& operator<<(Interaction *interaction);
};

#endif // SYSTEM_HPP
