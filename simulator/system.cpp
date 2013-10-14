#include <boost/numeric/odeint.hpp>

#include "system.hpp"

System::System() {
	phase = Phase(0);
}

int System::registerBody(Body* body) {
	return phase.registerBody(body);
}

int System::registerInteraction(Interaction* interaction) {
	interactions.push_back(interaction);
	return interactions.size() - 1;
}

Phase* System::getPhase() {
	return &phase;
}

double System::getEnergy() {
	double energy = 0;

	for (std::vector<Body*>::size_type i = 0; i < phase.getBodies().size(); i++) {
		energy += phase.getBodies()[i]->getKineticEnergy();
	}
	for (std::vector<Interaction*>::size_type i = 0; i < interactions.size(); i++) {
		energy += interactions[i]->getEnergy();
	}

	return energy;
}

void System::derive(const Phase& x, Phase& dxdt, const double t) {
	Phase::copyVelocitiesToPositions(x, dxdt);

	x.clearForces();

	for (std::vector<Interaction*>::size_type i = 0; i < interactions.size(); i++) {
		interactions[i]->apply(t);
	}

	x.devideForcesByMass();

	Phase::copyForcesToVelocities(x, dxdt);
}
