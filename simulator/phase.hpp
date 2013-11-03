#ifndef PHASE_HPP
#define PHASE_HPP

#include <cstddef>
#include <vector>
#include <boost/numeric/odeint.hpp>

struct vector3D {
	double x, y, z;
	vector3D(double a, double b, double c)
			: x(a), y(b), z(c) {
	}
};

class Phase: public std::vector<double> {

private:

	size_t length;
	mutable std::vector<double> forces;

public:

	Phase();
	void resize(size_t size);

	size_t createBody();

	vector3D getBodyPosition(size_t body) const;
	vector3D getBodyVelocity(size_t body) const;

	void setBodyPosition(size_t body, vector3D position);
	void setBodyVelocity(size_t body, vector3D velocity);

	void clearForces() const;
	void addForceOnBody(size_t body, vector3D force) const;

	static void copyVelocitiesToPositions(const Phase &x, Phase &dxdt);
	static void copyForcesToVelocities(const Phase &x, Phase &dxdt);
	static void devideForcesByMass(const Phase &x, const vector<double> &masses);
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
