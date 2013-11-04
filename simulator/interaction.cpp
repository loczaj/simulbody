#include <math.h>

#include "interaction.hpp"

void Interaction::setBodies(sizeT earth, sizeT moon) {
	this->earth = earth;
	this->moon = moon;
}

void Interaction::calculateR(const Phase &phase) {
	r = phase.getBodyPosition(moon);
	r -= phase.getBodyPosition(earth);
}

void Interaction::calculateV(const Phase &phase) {
	v = phase.getBodyVelocity(moon);
	v -= phase.getBodyVelocity(earth);
}

void Interaction::applyFOnMoon(const Phase &phase) {
	phase.addForceOnBody(moon, F);
}

void Interaction::applyFOnEarth(const Phase &phase) {
	phase.addForceOnBody(earth, F * -1.0);
}

Interaction::~Interaction() {
}
