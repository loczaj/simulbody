#include <math.h>
#include "coulomb.hpp"

CoulombInteraction::CoulombInteraction(double q1q2, Body* earth, Body* moon) {
	this->q1q2 = q1q2;
	this->setBodies(earth, moon);
}

void CoulombInteraction::apply(const double t) {

	calculateRxyzR2R();

	F = q1q2 / pow(r, 3);
	Fx = F * rx;
	Fy = F * ry;
	Fz = F * rz;

	applyFxyzOnMoon();
	applyFxyzOnEarth();
}

double CoulombInteraction::getEnergy() {
	calculateRxyzR2R();
	return q1q2 / r;
}

CoulombInteraction::~CoulombInteraction() {
}
