#ifndef PHASE_HPP
#define PHASE_HPP

#include <vector>
#include <boost/numeric/odeint.hpp>

typedef std::vector<double>::size_type sizeT;

struct vector3D {
	double x, y, z;
	vector3D(double a, double b, double c)
			: x(a), y(b), z(c) {
	}
};

class Phase: public std::vector<double> {

	friend class System;
	friend class Interaction;

private:

	sizeT numberOfBodies;
	mutable std::vector<double> forces;

	sizeT createBody();

	void clearForces() const;
	void addForceOnBody(sizeT body, const vector3D &force) const;

	static void copyVelocitiesToPositions(const Phase &x, Phase &dxdt);
	static void copyForcesToVelocities(const Phase &x, Phase &dxdt);
	static void devideForcesByMass(const Phase &x, const std::vector<double> &masses);

public:

	Phase();
	void resize(sizeT size);

	vector3D getBodyPosition(sizeT body) const;
	vector3D getBodyVelocity(sizeT body) const;

	void setBodyPosition(sizeT body, const vector3D position);
	void setBodyVelocity(sizeT body, const vector3D velocity);

};

// Phase bindings
namespace boost {
namespace numeric {
namespace odeint {

// Declare resizeability
template<>
struct is_resizeable<Phase> {
	typedef boost::true_type type;
	const static bool value = type::value;
};

// Define how to check size
template<>
struct same_size_impl<Phase, Phase> {
	static bool same_size(const Phase &v1, const Phase &v2) {
		return v1.size() == v2.size();
	}
};

// Define how to resize
template<>
struct resize_impl<Phase, Phase> {
	static void resize(Phase &v1, const Phase &v2) {
		v1.resize(v2.size());
	}
};
}
}
}

#endif /* PHASE_HPP */
