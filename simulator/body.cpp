#include "body.hpp"

Body::Body(double mass, double x, double y, double z, double vx, double vy, double vz) {
	this->mass = mass;

	this->x = x;
	this->y = y;
	this->z = z;
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;

	this->Fx = 0;
	this->Fy = 0;
	this->Fz = 0;
}

void Body::clearForce() const {
	Fx = 0;
	Fy = 0;
	Fz = 0;
}

void Body::devideForceByMass() const {
	Fx /= mass;
	Fy /= mass;
	Fz /= mass;
}

double Body::getKineticEnergy() const {
	return 0.5 * mass * (vx * vx + vy * vy + vz * vz);
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

// static member
void Body::copyVelocityToPosition(const Body* source, Body* target) {
	target->x = source->vx;
	target->y = source->vy;
	target->z = source->vz;
}

// static member
void Body::copyForceToVelocity(const Body* source, Body* target) {
	target->vx = source->Fx;
	target->vy = source->Fy;
	target->vz = source->Fz;
}

std::ostream& operator<<(std::ostream &out, const Body &body) {
	out << body.x << "\t" << body.y << "\t" << body.z << "\t" << body.vx << "\t" << body.vy << "\t"
			<< body.vz;
	return out;
}
