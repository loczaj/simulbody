#include "phase.hpp"

Phase::Phase() {
	bodies = *new std::vector<Body*>(0);
}

Phase::Phase(int size)
		: Phase() {
	resize(size);
}

int Phase::size() const {
	return bodies.size();
}

void Phase::resize(int size) {
	while (this->size() < size) {
		addBody(new Body());
	}
	while (this->size() > size) {
		bodies.pop_back();
	}
}

int Phase::addBody(Body* body) {
	bodies.push_back(body);
	return bodies.size() - 1;
}

std::vector<Body*> Phase::getBodies() {
	return bodies;
}

void Phase::clearForces() const {
	for (Body* body : bodies) {
		body->clearForce();
	}
}

void Phase::devideForcesByMass() const {
	for (Body* body : bodies) {
		body->devideForceByMass();
	}
}

Phase& Phase::operator +=(const Phase& p) {
	for (decltype(bodies.size()) i = 0; i < bodies.size(); i++) {
		*bodies[i] += *p.bodies[i];
	}
	return *this;
}

Phase& Phase::operator *=(const double a) {
	for (Body* body : bodies) {
		*body *= a;
	}
	return *this;
}

// static member
void Phase::copyVelocitiesToPositions(const Phase& source, Phase& target) {
	for (decltype(source.bodies.size()) i = 0; i < source.bodies.size(); i++) {
		Body::copyVelocityToPosition(source.bodies[i], target.bodies[i]);
	}
}

// static member
void Phase::copyForcesToVelocities(const Phase& source, Phase& target) {
	for (decltype(source.bodies.size()) i = 0; i < source.bodies.size(); i++) {
		Body::copyForceToVelocity(source.bodies[i], target.bodies[i]);
	}
}
