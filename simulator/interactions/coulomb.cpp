#include <math.h>
#include "coulomb.hpp"

CoulombInteraction::CoulombInteraction(double q1q2, size_t earth, size_t moon) {
	this->q1q2 = q1q2;
	this->setBodies(earth, moon);
}

void CoulombInteraction::apply(const Phase &phase, const double t) {

	calculateRxyzR2R(phase);

	F = q1q2 / pow(r, 3);
	Fx = F * rx;
	Fy = F * ry;
	Fz = F * rz;

	applyFxyzOnMoon(phase);
	applyFxyzOnEarth(phase);
}

double CoulombInteraction::getEnergy(const Phase &phase) {
	calculateRxyzR2R(phase);
	return q1q2 / r;
}

CoulombInteraction::~CoulombInteraction() {
}
