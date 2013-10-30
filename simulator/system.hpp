#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>

#include "interaction.hpp"
#include "phase.hpp"

class System {

	Phase phase;
	// TODO Add fields
	std::vector<Interaction*> interactions;

public:
	System();

	int addBody(Body* body);
	int addInteraction(Interaction* interaction);
	Phase* getPhase();
	double getEnergy();

	void derive(const Phase &x, Phase &dxdt, const double t);

	System& operator<<(Body* body);
	System& operator<<(Interaction* interaction);
};

#endif // SYSTEM_HPP
