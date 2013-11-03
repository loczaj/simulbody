#include <boost/numeric/odeint.hpp>
#include <algorithm>

#include "system.hpp"

sizeT System::createBody(double mass) {
	sizeT body = phase.createBody();

	masses.resize(body + 1);
	masses[body] = mass;

	return body;
}

sizeT System::createBody(double mass, vector3D position, vector3D velocity) {
	sizeT body = createBody(mass);

	setBodyPosition(body, position);
	setBodyVelocity(body, velocity);

	return body;
}

double System::getBodyMass(sizeT body) const {
	assert(body < masses.size());
	return masses[body];
}

vector3D System::getBodyPosition(sizeT body) const {
	return phase.getBodyPosition(body);
}

vector3D System::getBodyVelocity(sizeT body) const {
	return phase.getBodyVelocity(body);
}

void System::setBodyMass(sizeT body, double mass) {
	assert(body < masses.size());
	masses[body] = mass;
}

void System::setBodyPosition(sizeT body, vector3D position) {
	phase.setBodyPosition(body, position);
}

void System::setBodyVelocity(sizeT body, vector3D velocity) {
	phase.setBodyVelocity(body, velocity);
}

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

	Phase::devideForcesByMass(x, masses);

	Phase::copyForcesToVelocities(x, dxdt);
}

System& System::operator<<(Interaction *interaction) {
	this->addInteraction(interaction);
	return *this;
}
