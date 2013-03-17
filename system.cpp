#include <boost/numeric/odeint.hpp>

#include "system.hpp"

System::System() {
	phase = Phase();
}

int System::registerBody(Body* body) {
	return phase.registerBody(body);
}

int System::registerInteraction(Interaction* interaction) {
	interactions.push_back(interaction);
	return interactions.size() - 1;
}

void System::derive(const Phase& x, Phase& dxdt, const double t) {
	Phase::copyVelocityToPosition(x, dxdt);

	x.clearForce();

	for (std::vector<Interaction*>::size_type i = 0; i < interactions.size(); i++) {
		interactions[i]->actuate(t);
	}

	Phase::copyForceToVelocity(x, dxdt);
	dxdt.devideVelocityByMass();
}
