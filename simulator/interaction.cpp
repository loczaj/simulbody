#include <math.h>

#include "interaction.hpp"

void Interaction::setBodies(Body* earth, Body* moon) {
	this->earth = earth;
	this->moon = moon;
}

void Interaction::calculateRxyz() {
	rx = moon->x - earth->x;
	ry = moon->y - earth->y;
	rz = moon->z - earth->z;
}

void Interaction::calculateRxyzR2() {
	calculateRxyz();
	r2 = rx * rx + ry * ry + rz * rz;
}

void Interaction::calculateRxyzR2R() {
	calculateRxyzR2();
	r = sqrt(r2);
}

void Interaction::calculateVxyz() {
	vx = moon->vx - earth->vx;
	vy = moon->vy - earth->vy;
	vz = moon->vz - earth->vz;
}

void Interaction::calculateVxyzV2() {
	calculateVxyz();
	v2 = vx * vx + vy * vy + vz * vz;
}

void Interaction::calculateVxyzV2V() {
	calculateVxyzV2();
	v = sqrt(v2);
}

void Interaction::applyFxyzOnMoon() {
	moon->Fx += Fx;
	moon->Fy += Fy;
	moon->Fz += Fz;
}

void Interaction::applyFxyzOnEarth() {
	earth->Fx -= Fx;
	earth->Fy -= Fy;
	earth->Fz -= Fz;
}

Interaction::~Interaction() {
}
