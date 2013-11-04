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

sizeT System::getNumberOfBodies() const {
	return phase.numberOfBodies;
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

double System::getBodyKineticEnergy(sizeT body) const {
	vector3D v = getBodyVelocity(body);
	return 0.5 * getBodyMass(body) * (v.x * v.x + v.y * v.y + v.z * v.z);
}

double System::getSystemEnergy() const {
	double energy = 0.0;

	for (sizeT i = 0; i < getNumberOfBodies(); i++) {
		energy += getBodyKineticEnergy(i);
	}

	for (Interaction* interaction : interactions) {
		energy += interaction->getEnergy(phase);
	}

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
