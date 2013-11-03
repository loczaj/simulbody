#include <math.h>

#include "interaction.hpp"

void Interaction::setBodies(sizeT earth, sizeT moon) {
	this->earth = earth;
	this->moon = moon;
}

void Interaction::calculateRxyz(const Phase &phase) {
	vector3D rM = phase.getBodyPosition(moon);
	vector3D rE = phase.getBodyPosition(earth);

	rx = rM.x - rE.x;
	ry = rM.y - rE.y;
	rz = rM.z - rE.z;
}

void Interaction::calculateRxyzR2(const Phase &phase) {
	calculateRxyz(phase);
	r2 = rx * rx + ry * ry + rz * rz;
}

void Interaction::calculateRxyzR2R(const Phase &phase) {
	calculateRxyzR2(phase);
	r = sqrt(r2);
}

void Interaction::calculateVxyz(const Phase &phase) {
	vector3D vM = phase.getBodyVelocity(moon);
	vector3D vE = phase.getBodyVelocity(earth);

	vx = vM.x - vE.x;
	vy = vM.y - vE.y;
	vz = vM.z - vE.z;

}

void Interaction::calculateVxyzV2(const Phase &phase) {
	calculateVxyz(phase);
	v2 = vx * vx + vy * vy + vz * vz;
}

void Interaction::calculateVxyzV2V(const Phase &phase) {
	calculateVxyzV2(phase);
	v = sqrt(v2);
}

void Interaction::applyFxyzOnMoon(const Phase &phase) {
	phase.addForceOnBody(moon, vector3D(Fx, Fy, Fz));
}

void Interaction::applyFxyzOnEarth(const Phase &phase) {
	phase.addForceOnBody(earth, vector3D(-Fx, -Fy, -Fz));
}

Interaction::~Interaction() {
}
