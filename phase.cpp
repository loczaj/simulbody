#include "phase.hpp"

Phase::Phase() {
}

int Phase::registerBody(Body* body) {
	bodies.push_back(body);
	return bodies.size() - 1;
}

Phase& Phase::operator +=(const Phase& p) {
	for (std::vector<Body>::size_type i = 0; i < bodies.size() && i < p.bodies.size(); i++) {
		*bodies[i] += *p.bodies[i];
	}
	return *this;
}

Phase& Phase::operator *=(const double a) {
	for (std::vector<Body>::size_type i = 0; i < bodies.size(); i++) {
		*bodies[i] *= a;
	}
	return *this;
}
