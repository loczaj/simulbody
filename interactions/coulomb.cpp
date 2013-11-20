#include <math.h>
#include "coulomb.hpp"

CoulombInteraction::CoulombInteraction(double q1q2, identifier earth, identifier moon) {
	this->q1q2 = q1q2;
	this->setBodies(earth, moon);
}

void CoulombInteraction::apply(const Phase &phase, const double t) {

	calculateR(phase);

	factor = q1q2 / pow(r.abs(), 3);
	F = r;
	F *= factor;

	applyFOnMoon(phase);
	applyFOnEarth(phase);
}

double CoulombInteraction::getEnergy(const Phase &phase) {
	calculateR(phase);
	return q1q2 / r.abs();
}

CoulombInteraction::~CoulombInteraction() {
}
