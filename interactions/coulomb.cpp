#include <math.h>
#include "coulomb.hpp"

CoulombInteraction::CoulombInteraction(double q1q2) {
	this->q1q2 = q1q2;
}

void CoulombInteraction::affect(const double t) {

	calculateRxyzR2R();

	F = q1q2 / pow(r, 3);
	Fx = F * rx;
	Fy = F * ry;
	Fz = F * rz;

	affectFxyzOnApple();
	affectFxyzOnEarth();
}

double CoulombInteraction::energy() {
	calculateRxyzR2R();
	return -q1q2 / r;
}
