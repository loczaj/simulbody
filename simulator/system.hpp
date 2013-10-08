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

	int registerBody(Body* body);
	int registerInteraction(Interaction* interaction);
	Phase* getPhase();

	void derive(const Phase &x, Phase &dxdt, const double t);

};

#endif // SYSTEM_HPP
