#include "phase.hpp"

Phase::Phase() {
	bodies = *new std::vector<Body*>(0);
}

int Phase::size() const {
	return bodies.size();
}

void Phase::resize(int size) {
	while (this->size() < size) {
		registerBody(new Body());
	}
	while (this->size() > size) {
		bodies.pop_back();
	}
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
	for (std::vector<Body*>::size_type i = 0; i < source.bodies.size(); i++) {
		Body::copyVelocityToPosition(const_cast<Body*>(source.bodies[i]), target.bodies[i]);
	}
}

// static member
void Phase::copyForcesToVelocities(const Phase& source, Phase& target) {
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
