#include <math.h>
#include "gravity.hpp"

GravitationalInteraction::GravitationalInteraction(double gamma) {
	this->gamma = gamma;
	this->gammaM1M2 = 0.0;
}

void GravitationalInteraction::registerBodies(Body* earth, Body* moon) {
	Interaction::registerBodies(earth, moon);
	this->gammaM1M2 = gamma * earth->mass * moon->mass;
}

void GravitationalInteraction::apply(const double t) {

	calculateRxyzR2R();

	F = -gammaM1M2 / pow(r, 3);
	Fx = F * rx;
	Fy = F * ry;
	Fz = F * rz;

	applyFxyzOnMoon();
	applyFxyzOnEarth();
}

double GravitationalInteraction::getEnergy() {
	calculateRxyzR2R();
	return -gammaM1M2 / r;
}

GravitationalInteraction::~GravitationalInteraction() {
}
