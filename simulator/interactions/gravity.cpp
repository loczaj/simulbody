#include <math.h>
#include "gravity.hpp"

GravitationalInteraction::GravitationalInteraction(double gamma, Body* earth, Body* moon) {
	this->gamma = gamma;
	this->gammaM1M2 = 0.0;
	this->setBodies(earth, moon);
}

void GravitationalInteraction::setBodies(Body* earth, Body* moon) {
	Interaction::setBodies(earth, moon);
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
