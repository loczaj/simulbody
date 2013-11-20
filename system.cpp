#include <boost/numeric/odeint.hpp>
#include <algorithm>

#include "system.hpp"

identifier System::createBody(double mass) {
	identifier body = phase.createBody();

	masses.resize(body + 1);
	masses[body] = mass;

	return body;
}

identifier System::createBody(double mass, vector3D position, vector3D velocity) {
	identifier body = createBody(mass);

	setBodyPosition(body, position);
	setBodyVelocity(body, velocity);

	return body;
}

sizeT System::getNumberOfBodies() const {
	return phase.numberOfBodies;
}

double System::getBodyMass(identifier body) const {
	assert(body < masses.size());
	return masses[body];
}

double System::getBodyKineticEnergy(identifier body) const {
	vector3D v = getBodyVelocity(body);
	return 0.5 * getBodyMass(body) * v.scalarProduct(v);
}

double System::getBodyKineticEnergyReferenced(identifier body, identifier reference) const {
	vector3D v = getBodyVelocity(body) - getBodyVelocity(reference);
	return 0.5 * getBodyMass(body) * v.scalarProduct(v);
}

double System::getBodyPotentialEnergy(identifier body) const {
	double energy = 0.0;
	for (Interaction* interaction : interactions) {
		if (interaction->earth == body || interaction->moon == body) {
			energy += interaction->getEnergy(phase);
		}
	}
	return energy;
}

double System::getPairPotentialEnergy(identifier earth, identifier moon) const {
	double energy = 0.0;
	for (Interaction* interaction : interactions) {
		if ((interaction->earth == earth && interaction->moon == moon)
				|| (interaction->earth == moon && interaction->moon == earth)) {
			energy += interaction->getEnergy(phase);
		}
	}
	return energy;
}

vector3D System::getBodyPosition(identifier body) const {
	return phase.getBodyPosition(body);
}

vector3D System::getBodyVelocity(identifier body) const {
	return phase.getBodyVelocity(body);
}

vector3D System::getBodyImpulse(identifier body) const {
	vector3D velocity = getBodyVelocity(body);
	return velocity * getBodyMass(body);
}

void System::setBodyMass(identifier body, double mass) {
	assert(body < masses.size());
	masses[body] = mass;
}

void System::setBodyPosition(identifier body, vector3D position) {
	phase.setBodyPosition(body, position);
}

void System::setBodyVelocity(identifier body, vector3D velocity) {
	phase.setBodyVelocity(body, velocity);
}

double System::getSystemMass() const {
	double mass = 0.0;
	for (identifier i = 0; i < getNumberOfBodies(); i++) {
		mass += getBodyMass(i);
	}

	return mass;
}

double System::getSystemEnergy() const {
	double energy = 0.0;
	for (identifier i = 0; i < getNumberOfBodies(); i++) {
		energy += getBodyKineticEnergy(i);
	}
	for (Interaction* interaction : interactions) {
		energy += interaction->getEnergy(phase);
	}

	return energy;
}

vector3D System::getSystemCenterOfMass() const {
	vector3D centerOfMass;
	for (size_t i = 0; i < getNumberOfBodies(); i++) {
		centerOfMass += getBodyPosition(i) * getBodyMass(i);
	}

	centerOfMass /= getSystemMass();
	return centerOfMass;
}

vector3D System::getSystemImpulse() const {
	vector3D impulse;
	for (size_t i = 0; i < getNumberOfBodies(); i++) {
		impulse += getBodyImpulse(i);
	}

	return impulse;
}

std::pair<vector3D, vector3D> System::convertToCenterOfMassSystem() {
	vector3D systemCenterOfMass = getSystemCenterOfMass();
	vector3D systemVelocity = getSystemImpulse() / getSystemMass();

	for (size_t i = 0; i < getNumberOfBodies(); i++) {
		setBodyPosition(i, getBodyPosition(i) - systemCenterOfMass);
		setBodyVelocity(i, getBodyVelocity(i) - systemVelocity);
	}

	std::pair<vector3D, vector3D> center(systemCenterOfMass, systemVelocity);
	return center;
}

void System::addInteraction(Interaction *interaction) {
	interactions.push_back(interaction);
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
