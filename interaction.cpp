#include <math.h>
#include "interaction.hpp"

void Interaction::registerBodies(Body* earth, Body* apple) {
	this->earth = earth;
	this->apple = apple;
}

void Interaction::calculateRxyz() {
	rx = apple->x - earth->x;
	ry = apple->y - earth->y;
	rz = apple->z - earth->z;
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
	vx = apple->vx - earth->vx;
	vy = apple->vy - earth->vy;
	vz = apple->vz - earth->vz;
}

void Interaction::calculateVxyzV2() {
	calculateVxyz();
	v2 = vx * vx + vy * vy + vz * vz;
}

void Interaction::calculateVxyzV2V() {
	calculateVxyzV2();
	v = sqrt(v2);
}

void Interaction::affectFxyzOnApple() {
	apple->Fx += Fx;
	apple->Fy += Fy;
	apple->Fz += Fz;
}

void Interaction::affectFxyzOnEarth() {
	earth->Fx -= Fx;
	earth->Fy -= Fy;
	earth->Fz -= Fz;
}

Interaction::~Interaction() {
}
