#include <assert.h>

#include "phase.hpp"

namespace simulbody {

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
}

sizeT Phase::getNumberOfBodies() const {
	return numberOfBodies;
}

identifier Phase::createBody() {
	assert(size() % 6 == 0);
	int id = numberOfBodies++;

	std::vector<double>::resize(6 * (id + 1));

	return id;
}

vector3D Phase::getBodyPosition(identifier body) const {
	assert(body < numberOfBodies);
	return vector3D(at(6 * body + Coord::x), at(6 * body + Coord::y), at(6 * body + Coord::z));
}

vector3D Phase::getBodyVelocity(identifier body) const {
	assert(body < numberOfBodies);
	return vector3D(at(6 * body + Coord::vx), at(6 * body + Coord::vy), at(6 * body + Coord::vz));
}

void Phase::setBodyPosition(identifier body, const vector3D position) {
	assert(body < numberOfBodies);

	at(6 * body + Coord::x) = position.x;
	at(6 * body + Coord::y) = position.y;
	at(6 * body + Coord::z) = position.z;
}

void Phase::setBodyVelocity(identifier body, const vector3D velocity) {
	assert(body < numberOfBodies);

	at(6 * body + Coord::vx) = velocity.x;
	at(6 * body + Coord::vy) = velocity.y;
	at(6 * body + Coord::vz) = velocity.z;
}

void Phase::addForceOnBodyInDifferentialPhase(identifier body, const vector3D &force) {
	assert(body < numberOfBodies);

	operator[](6 * body + Coord::vx) += force.x;
	operator[](6 * body + Coord::vy) += force.y;
	operator[](6 * body + Coord::vz) += force.z;
}

void Phase::addVelocityOnBodyInDifferentialPhase(identifier body, const vector3D &velocity) {
	assert(body < numberOfBodies);

	operator[](6 * body + Coord::x) += velocity.x;
	operator[](6 * body + Coord::y) += velocity.y;
	operator[](6 * body + Coord::z) += velocity.z;
}

// static
void Phase::clearVelocities(Phase &x) {
	for (identifier body = 0; body < x.numberOfBodies; body++) {
		x[6 * body + Coord::vx] = 0.0;
		x[6 * body + Coord::vy] = 0.0;
		x[6 * body + Coord::vz] = 0.0;
	}
}

// static
void Phase::copyVelocitiesToPositions(const Phase &x, Phase &dxdt) {
	for (identifier body = 0; body < x.numberOfBodies; body++) {
		dxdt[6 * body + Coord::x] = x[6 * body + Coord::vx];
		dxdt[6 * body + Coord::y] = x[6 * body + Coord::vy];
		dxdt[6 * body + Coord::z] = x[6 * body + Coord::vz];
	}
}

// static
void Phase::devideVelocities(Phase &x, const std::vector<double> &divisors) {
	for (identifier body = 0; body < x.numberOfBodies; body++) {
		x[6 * body + Coord::vx] /= divisors[body];
		x[6 * body + Coord::vy] /= divisors[body];
		x[6 * body + Coord::vz] /= divisors[body];
	}
}

} /* NAMESPACE SIMULBODY */

