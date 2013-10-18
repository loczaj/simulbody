#include <boost/numeric/odeint.hpp>

#include "system.hpp"

System::System() {
	phase = Phase();
}

int System::addBody(Body* body) {
	return phase.addBody(body);
}

int System::addInteraction(Interaction* interaction) {
	interactions.push_back(interaction);
	return interactions.size() - 1;
}

Phase* System::getPhase() {
	return &phase;
}

double System::getEnergy() {
	double energy = 0;

	for (Body* body : phase.getBodies()) {
		energy += body->getKineticEnergy();
	}
	for (Interaction* interaction : interactions) {
		energy += interaction->getEnergy();
	}

	return energy;
}

void System::derive(const Phase& x, Phase& dxdt, const double t) {
	Phase::copyVelocitiesToPositions(x, dxdt);

	x.clearForces();

	for (Interaction* interaction : interactions) {
		interaction->apply(t);
	}

	x.devideForcesByMass();

	Phase::copyForcesToVelocities(x, dxdt);
}

System& System::operator<<(Body* body) {
	this->addBody(body);
	return *this;
}

System& System::operator<<(Interaction* interaction) {
	this->addInteraction(interaction);
	return *this;
}
