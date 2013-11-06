#include <assert.h>

#include "phase.hpp"

Phase::Phase() {
	numberOfBodies = 0;
}

Phase::Phase(sizeT size)
		: Phase() {
	resize(size);
}

void Phase::resize(sizeT size) {
	assert(size % 6 == 0);
	numberOfBodies = size / 6;

	std::vector<double>::resize(size);
	forces.resize(numberOfBodies * 3);
}

sizeT Phase::createBody() {
	assert(size() % 6 == 0);
	int id = numberOfBodies++;

	std::vector<double>::resize(6 * (id + 1));
	forces.resize(3 * (id + 1));

	return id;
}

vector3D Phase::getBodyPosition(sizeT body) const {
	assert(body < numberOfBodies);
	return vector3D(at(6 * body + Coord::x), at(6 * body + Coord::y), at(6 * body + Coord::z));
}

vector3D Phase::getBodyVelocity(sizeT body) const {
	assert(body < numberOfBodies);
	return vector3D(at(6 * body + Coord::vx), at(6 * body + Coord::vy), at(6 * body + Coord::vz));
}

void Phase::setBodyPosition(sizeT body, const vector3D position) {
	assert(body < numberOfBodies);

	at(6 * body + Coord::x) = position.x;
	at(6 * body + Coord::y) = position.y;
	at(6 * body + Coord::z) = position.z;
}

void Phase::setBodyVelocity(sizeT body, const vector3D velocity) {
	assert(body < numberOfBodies);

	at(6 * body + Coord::vx) = velocity.x;
	at(6 * body + Coord::vy) = velocity.y;
	at(6 * body + Coord::vz) = velocity.z;
}

void Phase::clearForces() const {
	std::fill(forces.begin(), forces.end(), 0.0);
}

void Phase::addForceOnBody(sizeT body, const vector3D &force) const {
	assert(body < numberOfBodies);

	forces[3 * body + Coord::x] += force.x;
	forces[3 * body + Coord::y] += force.y;
	forces[3 * body + Coord::z] += force.z;
}

// static
void Phase::copyVelocitiesToPositions(const Phase &x, Phase &dxdt) {
	for (sizeT body = 0; body < x.numberOfBodies; body++) {
		dxdt[6 * body + Coord::x] = x[6 * body + Coord::vx];
		dxdt[6 * body + Coord::y] = x[6 * body + Coord::vy];
		dxdt[6 * body + Coord::z] = x[6 * body + Coord::vz];
	}
}

// static
void Phase::copyForcesToVelocities(const Phase &x, Phase &dxdt) {
	for (sizeT body = 0; body < x.numberOfBodies; body++) {
		dxdt[6 * body + Coord::vx] = x.forces[3 * body + Coord::x];
		dxdt[6 * body + Coord::vy] = x.forces[3 * body + Coord::y];
		dxdt[6 * body + Coord::vz] = x.forces[3 * body + Coord::z];
	}
}

// static
void Phase::devideForcesByMass(const Phase &x, const std::vector<double> &masses) {
	for (sizeT body = 0; body < x.numberOfBodies; body++) {
		x.forces[3 * body + Coord::x] /= masses[body];
		x.forces[3 * body + Coord::y] /= masses[body];
		x.forces[3 * body + Coord::z] /= masses[body];
	}
}
