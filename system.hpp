#include <vector>

#include "phase.hpp"
#include "interaction.hpp"

class System {

	Phase phase;
	std::vector<Interaction*> interactions;

public:
	System();

	int registerBody(Body* body);
	int registerInteraction(Interaction* interaction);

	void operator()(const Phase &x, Phase &dxdt, const double t);

};
