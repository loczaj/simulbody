#include <math.h>
#include "gravity.hpp"

static double factor;

GravitationalInteraction::GravitationalInteraction(double gammaM1M2, sizeT earth, sizeT moon) {
	this->gammaM1M2 = gammaM1M2;
	this->setBodies(earth, moon);
}

void GravitationalInteraction::apply(const Phase &phase, const double t) {

	calculateR(phase);

	factor = -gammaM1M2 / pow(r.abs(), 3);
	F = r * factor;

	applyFOnMoon(phase);
	applyFOnEarth(phase);
}

double GravitationalInteraction::getEnergy(const Phase &phase) {
	calculateR(phase);
	return -gammaM1M2 / r.abs();
}

GravitationalInteraction::~GravitationalInteraction() {
}
