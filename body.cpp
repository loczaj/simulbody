#include "body.hpp"

Body& Body::operator +=(const Body& b) {
	x += b.x;
	y += b.y;
	z += b.z;

	vx += b.vx;
	vy += b.vy;
	vz += b.vz;

	return *this;
}

Body& Body::operator *=(const double a) {
	x *= a;
	y *= a;
	z *= a;

	vx *= a;
	vy *= a;
	vz *= a;

	return *this;
}
