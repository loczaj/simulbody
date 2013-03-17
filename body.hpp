#ifndef BODY_HPP
#define BODY_HPP

class Body {

public:
	double mass;

	double x, y, z;
	double vx, vy, vz;
	double Fx, Fy, Fz;

	void clearForce();
	void devideVelocityByMass();

	Body& operator +=(const Body& b);
	Body& operator *=(const double a);

	static void copyVelocityToPosition(const Body* source, Body* target);
	static void copyForceToVelocity(const Body* source, Body* target);
};

#endif // BODY_HPP
