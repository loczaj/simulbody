#ifndef BODY_HPP
#define BODY_HPP

class Body {

public:
	double mass;

	double x, y, z;
	double vx, vy, vz;

	Body& operator +=(const Body& b);
	Body& operator *=(const double a);
};

#endif // BODY_HPP
