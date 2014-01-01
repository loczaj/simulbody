#ifndef PHASE_HPP
#define PHASE_HPP

#include <vector>
#include <boost/numeric/odeint.hpp>

#include "vector3d.hpp"

namespace simulbody {

typedef std::vector<double>::size_type identifier;
typedef std::vector<double>::size_type sizeT;

enum Coord
	: sizeT {
		x = 0, y = 1, z = 2, vx = 3, vy = 4, vz = 5
};

class Phase: public std::vector<double> {

	friend class System;
	friend class Interaction;

private:

	sizeT numberOfBodies;

	identifier createBody();

	void addForceOnBodyInDifferentialPhase(identifier body, const vector3D &force);
	void addVelocityOnBodyInDifferentialPhase(identifier body, const vector3D &velocity);

	static void clearVelocities(Phase &x);
	static void copyVelocitiesToPositions(const Phase &x, Phase &dxdt);
	static void devideVelocities(Phase &x, const std::vector<double> &divisors);

public:

	Phase();
	Phase(sizeT size);
	void resize(sizeT size);
	sizeT getNumberOfBodies() const;

	vector3D getBodyPosition(identifier body) const;
	vector3D getBodyVelocity(identifier body) const;

	void setBodyPosition(identifier body, const vector3D position);
	void setBodyVelocity(identifier body, const vector3D velocity);

};
} /* NAMESPACE SIMULBODY */

inline std::ostream& operator<<(std::ostream &out, const simulbody::Phase &p) {
	for (simulbody::sizeT i = 0; i < p.size(); i++) {
		out << p.at(i);
		if (i < p.size() - 1)
			out << "\t";
	}
	return out;
}

// Phase bindings
namespace boost {
namespace numeric {
namespace odeint {

// Declare ability to resize
template<>
struct is_resizeable<simulbody::Phase> {
	typedef boost::true_type type;
	const static bool value = type::value;
};

// Define how to check size
template<>
struct same_size_impl<simulbody::Phase, simulbody::Phase> {
	static bool same_size(const simulbody::Phase &v1, const simulbody::Phase &v2) {
		return v1.size() == v2.size();
	}
};

// Define how to resize
template<>
struct resize_impl<simulbody::Phase, simulbody::Phase> {
	static void resize(simulbody::Phase &v1, const simulbody::Phase &v2) {
		v1.resize(v2.size());
	}
};
}
}
}

#endif /* PHASE_HPP */
