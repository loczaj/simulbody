#include <math.h>

#include "interaction.hpp"

namespace simulbody {

void Interaction::setBodies(identifier earth, identifier moon) {
	this->earth = earth;
	this->moon = moon;
}

void Interaction::calculateR(const Phase &x) {
	r = x.getBodyPosition(moon);
	r -= x.getBodyPosition(earth);
}

void Interaction::calculateV(const Phase &x) {
	v = x.getBodyVelocity(moon);
	v -= x.getBodyVelocity(earth);
}

void Interaction::applyFOnMoon(Phase &dxdt) {
	dxdt.addForceOnBodyInDifferentialPhase(moon, F);
}

void Interaction::applyFOnEarth(Phase &dxdt) {
	dxdt.addForceOnBodyInDifferentialPhase(earth, -F);
}

Interaction::~Interaction() {
}

} /* NAMESPACE SIMULBODY */
