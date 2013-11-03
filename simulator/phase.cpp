#include <assert.h>

#include "phase.hpp"

#define pos_X 0
#define pos_Y 1
#define pos_Z 2
#define pos_Vx 3
#define pos_Vy 4
#define pos_Vz 5

void Phase::setSize(const Phase &ref) {
	std::vector<double>::resize(ref.size());

	length = ref.length;
	forces.resize(ref.forces.size());
	masses = ref.masses;
}

size_t Phase::createBody(double mass) {
	assert(size() % 6 == 0);

	int id = length++;
	std::vector<double>::resize(6 * (id + 1));

	forces.resize(3 * (id + 1));

	masses.resize(id + 1);
	masses[id] = mass;

	return id;
}

size_t Phase::createBody(double mass, vector3D position, vector3D velocity) {
	int body = createBody(mass);
	setBodyPosition(body, position);
	setBodyVelocity(body, velocity);
	return body;
}

double Phase::getBodyMass(size_t body) const {
	assert(body < masses.size());
	return masses[body];
}

vector3D Phase::getBodyPosition(size_t body) const {
	assert(body < length);
	return vector3D(at(6 * body + pos_X), at(6 * body + pos_Y), at(6 * body + pos_Z));
}

vector3D Phase::getBodyVelocity(size_t body) const {
	assert(body < length);
	return vector3D(at(6 * body + pos_Vx), at(6 * body + pos_Vy), at(6 * body + pos_Vz));
}

void Phase::setBodyMass(size_t body, double mass) {
	assert(body < masses.size());
	masses[body] = mass;
}

void Phase::setBodyPosition(size_t body, vector3D position) {
	assert(body < length);

	at(6 * body + pos_X) = position.x;
	at(6 * body + pos_Y) = position.y;
	at(6 * body + pos_Z) = position.y;
}

void Phase::setBodyVelocity(size_t body, vector3D velocity) {
	assert(body < length);

	at(6 * body + pos_Vx) = velocity.x;
	at(6 * body + pos_Vy) = velocity.y;
	at(6 * body + pos_Vz) = velocity.y;
}

void Phase::clearForces() const {
	std::fill(forces.begin(), forces.end(), 0.0);
}

void Phase::addForceOnBody(size_t body, vector3D force) const {
	assert(body < length);

	forces[3 * body + pos_X] += force.x;
	forces[3 * body + pos_Y] += force.y;
	forces[3 * body + pos_Z] += force.z;
}

// static
void Phase::copyVelocitiesToPositions(const Phase &x, Phase &dxdt) {
	for (size_t body = 0; body < x.length; body++) {
		dxdt[6 * body + pos_X] = x[6 * body + pos_Vx];
		dxdt[6 * body + pos_Y] = x[6 * body + pos_Vy];
		dxdt[6 * body + pos_Z] = x[6 * body + pos_Vz];
	}
}

// static
void Phase::copyForcesToVelocities(const Phase &x, Phase &dxdt) {
	for (size_t body = 0; body < x.length; body++) {
		dxdt[6 * body + pos_Vx] = x.forces[3 * body + pos_X];
		dxdt[6 * body + pos_Vy] = x.forces[3 * body + pos_Y];
		dxdt[6 * body + pos_Vz] = x.forces[3 * body + pos_Z];
	}
}

// static
void Phase::devideForcesByMass(const Phase &x) {
	for (size_t body = 0; body < x.length; body++) {
		x.forces[3 * body + pos_X] /= x.masses[body];
		x.forces[3 * body + pos_Y] /= x.masses[body];
		x.forces[3 * body + pos_Z] /= x.masses[body];
	}
}
