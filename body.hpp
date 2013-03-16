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

	static void copyVelocityToPosition(const Body& source, Body& target);
	static void copyForceToVelocity(const Body& source, Body& target);

	Body& operator +=(const Body& b);
	Body& operator *=(const double a);
};

#endif // BODY_HPP
