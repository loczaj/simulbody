#include "body.hpp"

void Body::clearForce() {
	Fx = 0;
	Fy = 0;
	Fz = 0;
}

void Body::copyVelocityToPosition(const Body& source, Body& target) {
	target.x = source.vx;
	target.y = source.vy;
	target.z = source.vz;
}

void Body::copyForceToVelocity(const Body& source, Body& target) {
	target.vx = source.Fx;
	target.vy = source.Fy;
	target.vz = source.Fz;
}

void Body:: devideVelocityByMass() {
	vx /= mass;
	vy /= mass;
	vz /= mass;
}

Body& Body::operator +=(const Body& b) {
	x += b.x;
	y += b.y;
	z += b.z;

	vx += b.vx;
	vy += b.vy;
	vz += b.vz;

	// Skip F. as it is not part of the phase

	return *this;
}

Body& Body::operator *=(const double a) {
	x *= a;
	y *= a;
	z *= a;

	vx *= a;
	vy *= a;
	vz *= a;

	// Skip F. as it is not part of the phase

	return *this;
}
