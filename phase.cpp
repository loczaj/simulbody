#include "phase.hpp"
#include "assert.h"

Phase::Phase() {
}

int Phase::registerBody(Body& body) {
	bodies.push_back(&body);
	return bodies.size() - 1;
}

Phase& Phase::operator +=(const Phase& p) {
	assert(bodies.size() == p.bodies.size());
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		*bodies[i] += *p.bodies[i];
	}
	return *this;
}

void Phase::clearForce() const {
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		bodies[i]->clearForce();
	}
}

void Phase::devideVelocityByMass() {
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		bodies[i]->devideVelocityByMass();
	}
}

Phase& Phase::operator *=(const double a) {
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		*bodies[i] *= a;
	}
	return *this;
}

void Phase::copyVelocityToPosition(const Phase& source, Phase& target) {
	assert(source.bodies.size() == target.bodies.size());
	for (std::vector<Body*>::size_type i = 0; i < source.bodies.size(); i++) {
		Body::copyVelocityToPosition(const_cast<Body&>(*source.bodies[i]), *target.bodies[i]);
	}
}

void Phase::copyForceToVelocity(const Phase& source, Phase& target) {
	assert(source.bodies.size() == target.bodies.size());
	for (std::vector<Body*>::size_type i = 0; i < source.bodies.size(); i++) {
		Body::copyForceToVelocity(const_cast<Body&>(*source.bodies[i]), *target.bodies[i]);
	}
}
