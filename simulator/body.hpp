#ifndef BODY_HPP
#define BODY_HPP

class Body {

public:
	double mass;

	double x, y, z;
	double vx, vy, vz;
	mutable double Fx, Fy, Fz;

	Body();
	Body(double mass, double x = 0, double y = 0, double z = 0, double vx = 0, double vy = 0, double vz = 0);

	void clearForce() const;
	void devideForceByMass() const;
	double getKineticEnergy() const;

	Body& operator +=(const Body& b);
	Body& operator *=(const double a);

	static void copyVelocityToPosition(const Body* source, Body* target);
	static void copyForceToVelocity(const Body* source, Body* target);
};

#endif // BODY_HPP
