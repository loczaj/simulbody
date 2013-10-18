#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>

#include "phase.hpp"
#include "interaction.hpp"

class System {

	Phase phase;
	std::vector<Interaction*> interactions;
// TODO Add fields

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
