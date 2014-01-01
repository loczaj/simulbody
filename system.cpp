#include <boost/numeric/odeint.hpp>
#include <algorithm>

#include "system.hpp"

namespace simulbody {

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

std::vector<identifier> System::getBodies() const {
	std::vector<identifier> result;
	for (identifier id = 0; id < getNumberOfBodies(); id++) {
		result.push_back(id);
	}
	return result;
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
	return getBodyKineticEnergyReferenced(body, getBodyVelocity(reference));
}

double System::getBodyKineticEnergyReferenced(identifier body, vector3D referenceVelocity) const {
	vector3D v = getBodyVelocity(body) - referenceVelocity;
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

vector3D System::getBodyAngularMomentum(identifier body, identifier reference) const {
	vector3D r = getBodyPosition(body) - getBodyPosition(reference);
	vector3D v = getBodyVelocity(body) - getBodyVelocity(reference);
	return r.vectorProduct(v) * getBodyMass(body);
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

vector3D System::getGroupCenterOfMass(std::vector<identifier> bodyGroup) const {
	vector3D centerOfMass;
	double mass = 0.0;
	for (identifier body : bodyGroup) {
		centerOfMass += getBodyPosition(body) * getBodyMass(body);
		mass += getBodyMass(body);
	}

	centerOfMass /= mass;
	return centerOfMass;
}

vector3D System::getGroupImpulse(std::vector<identifier> bodyGroup) const {
	vector3D impulse;
	for (identifier body : bodyGroup) {
		impulse += getBodyImpulse(body);
	}
	return impulse;
}

double System::getGroupMass(std::vector<identifier> bodyGroup) const {
	double mass = 0.0;
	for (identifier body : bodyGroup) {
		mass += getBodyMass(body);
	}
	return mass;
}

double System::getSystemMass() const {
	return getGroupMass(getBodies());
}

double System::getSystemEnergy() const {
	double energy = 0.0;
	for (identifier body : getBodies()) {
		energy += getBodyKineticEnergy(body);
	}
	for (Interaction* interaction : interactions) {
		energy += interaction->getEnergy(phase);
	}

	return energy;
}

vector3D System::getSystemCenterOfMass() const {
	return getGroupCenterOfMass(getBodies());
}

vector3D System::getSystemImpulse() const {
	return getGroupImpulse(getBodies());
}

std::pair<vector3D, vector3D> System::convertToCenterOfMassSystem() {
	vector3D systemCenterOfMass = getSystemCenterOfMass();
	vector3D systemVelocity = getSystemImpulse() / getSystemMass();

	for (identifier body : getBodies()) {
		setBodyPosition(body, getBodyPosition(body) - systemCenterOfMass);
		setBodyVelocity(body, getBodyVelocity(body) - systemVelocity);
	}

	std::pair<vector3D, vector3D> center(systemCenterOfMass, systemVelocity);
	return center;
}

void System::addInteraction(Interaction *interaction) {
	interactions.push_back(interaction);
}

void System::derive(const Phase &x, Phase &dxdt, const double t) const {

	Phase::copyVelocitiesToPositions(x, dxdt);
	Phase::clearVelocities(dxdt);

	for (Interaction* interaction : interactions) {
		interaction->apply(x, dxdt, t);
	}

	Phase::devideVelocities(dxdt, masses);
}

System& System::operator<<(Interaction *interaction) {
	this->addInteraction(interaction);
	return *this;
}

} /* NAMESPACE SIMULBODY */

