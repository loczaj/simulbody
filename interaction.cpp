#include <math.h>

#include "interaction.hpp"

namespace simulbody {

void Interaction::setBodies(identifier earth, identifier moon) {
	this->earth = earth;
	this->moon = moon;
}

void Interaction::calculateRelativePositionR(const Phase &x) {
	r = x.getBodyPosition(moon);
	r -= x.getBodyPosition(earth);
}

void Interaction::calculateRelativeVelocityV(const Phase &x) {
	v = x.getBodyVelocity(moon);
	v -= x.getBodyVelocity(earth);
}

void Interaction::applyForceOnMoon(Phase &dxdt, const vector3D &force) {
	dxdt.addForceOnBodyInDifferentialPhase(moon, force);
}

void Interaction::applyForceOnEarth(Phase &dxdt, const vector3D &force) {
	dxdt.addForceOnBodyInDifferentialPhase(earth, force);
}

void Interaction::addCollateralVelocityOnMoon(Phase &dxdt, const vector3D &velocity) {
	dxdt.addVelocityOnBodyInDifferentialPhase(moon, velocity);
}

void Interaction::addCollateralVelocityOnEarth(Phase &dxdt, const vector3D &velocity) {
	dxdt.addVelocityOnBodyInDifferentialPhase(earth, velocity);
}

Interaction::~Interaction() {
}

} /* NAMESPACE SIMULBODY */
