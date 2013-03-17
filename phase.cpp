#include "phase.hpp"
#include "assert.h"

Phase::Phase() {
}

int Phase::registerBody(Body* body) {
	bodies.push_back(body);
	return bodies.size() - 1;
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

Phase& Phase::operator +=(const Phase& p) {
	assert(bodies.size() == p.bodies.size());
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		*bodies[i] += *p.bodies[i];
	}
	return *this;
}

Phase& Phase::operator *=(const double a) {
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		*bodies[i] *= a;
	}
	return *this;
}

// static member
void Phase::copyVelocityToPosition(const Phase& source, Phase& target) {
	assert(source.bodies.size() == target.bodies.size());
	for (std::vector<Body*>::size_type i = 0; i < source.bodies.size(); i++) {
		Body::copyVelocityToPosition(const_cast<Body*>(source.bodies[i]), target.bodies[i]);
	}
}

// static member
void Phase::copyForceToVelocity(const Phase& source, Phase& target) {
	assert(source.bodies.size() == target.bodies.size());
	for (std::vector<Body*>::size_type i = 0; i < source.bodies.size(); i++) {
		Body::copyForceToVelocity(const_cast<Body*>(source.bodies[i]), target.bodies[i]);
	}
}

std::ostream& operator<<(std::ostream &out, const Phase &phase) {
	for (std::vector<Body*>::size_type i = 0; i < phase.bodies.size() - 1; i++) {
		out << *phase.bodies[i] << "\t";
	}
	out << *phase.bodies[phase.bodies.size() - 1] << std::endl;
	return out;
}
