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
	std::vector<double> masses;
	mutable std::vector<double> forces;

public:

	void setSize(const Phase &ref);

	size_t createBody(double mass);
	size_t createBody(double mass, vector3D position, vector3D velocity);

	double getBodyMass(size_t body) const;
	vector3D getBodyPosition(size_t body) const;
	vector3D getBodyVelocity(size_t body) const;

	void setBodyMass(size_t body, double mass);
	void setBodyPosition(size_t body, vector3D position);
	void setBodyVelocity(size_t body, vector3D velocity);

	void clearForces() const;
	void addForceOnBody(size_t body, vector3D force) const;

	static void copyVelocitiesToPositions(const Phase &x, Phase &dxdt);
	static void copyForcesToVelocities(const Phase &x, Phase &dxdt);
	static void devideForcesByMass(const Phase &x);
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
		v1.setSize(v2);
	}
};
}
}
}

#endif /* PHASE_HPP */
