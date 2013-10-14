#include "phase.hpp"
#include "assert.h"

Phase::Phase() {
	// FIXME proper constructor
	// std::cout << "Phase" << std::endl;
	bodies = *new std::vector<Body*>(2);
	bodies[0] = new Body(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
	bodies[1] = new Body(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
}

Phase::Phase(int n) {
	// FIXME proper constructor
	// std::cout << "Phase " << n << std::endl;
	bodies = *new std::vector<Body*>(n);
}

int Phase::registerBody(Body* body) {
	bodies.push_back(body);
	return bodies.size() - 1;
}

std::vector<Body*> Phase::getBodies() {
	return bodies;
}

void Phase::clearForces() const {
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		bodies[i]->clearForce();
	}
}

void Phase::devideForcesByMass() const {
	for (std::vector<Body*>::size_type i = 0; i < bodies.size(); i++) {
		bodies[i]->devideForceByMass();
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
void Phase::copyVelocitiesToPositions(const Phase& source, Phase& target) {
	//std::cout << source.bodies.size();
	//std::cout << target.bodies.size() << std::endl;
	assert(source.bodies.size() == target.bodies.size());
	for (std::vector<Body*>::size_type i = 0; i < source.bodies.size(); i++) {
		Body::copyVelocityToPosition(const_cast<Body*>(source.bodies[i]), target.bodies[i]);
	}
}

// static member
void Phase::copyForcesToVelocities(const Phase& source, Phase& target) {
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
