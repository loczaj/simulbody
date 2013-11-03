#include <math.h>
#include "gravity.hpp"

GravitationalInteraction::GravitationalInteraction(double gammaM1M2, sizeT earth, sizeT moon) {
	this->gammaM1M2 = gammaM1M2;
	this->setBodies(earth, moon);
}

void GravitationalInteraction::apply(const Phase &phase, const double t) {

	calculateRxyzR2R(phase);

	F = -gammaM1M2 / pow(r, 3);
	Fx = F * rx;
	Fy = F * ry;
	Fz = F * rz;

	applyFxyzOnMoon(phase);
	applyFxyzOnEarth(phase);
}

double GravitationalInteraction::getEnergy(const Phase &phase) {
	calculateRxyzR2R(phase);
	return -gammaM1M2 / r;
}

GravitationalInteraction::~GravitationalInteraction() {
}
