#include <boost/numeric/odeint.hpp>
#include <algorithm>

#include "system.hpp"

void System::addInteraction(Interaction *interaction) {
	interactions.push_back(interaction);
}

double System::getEnergy() {
	double energy = 0;

//	for (Body* body : phase.getBodies()) {
//		energy += body->getKineticEnergy();
//	}
//	for (Interaction* interaction : interactions) {
//		energy += interaction->getEnergy();
//	}

	return energy;
}

void System::derive(const Phase &x, Phase &dxdt, const double t) const {

	Phase::copyVelocitiesToPositions(x, dxdt);

	x.clearForces();

	for (Interaction* interaction : interactions) {
		interaction->apply(x, t);
	}

	Phase::devideForcesByMass(x);

	Phase::copyForcesToVelocities(x, dxdt);
}

System& System::operator<<(Interaction *interaction) {
	this->addInteraction(interaction);
	return *this;
}
