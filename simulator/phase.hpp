#ifndef PHASE_HPP
#define PHASE_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <boost/operators.hpp>
#include <boost/numeric/odeint.hpp>

#include "body.hpp"

class Phase: boost::additive1<Phase, boost::additive2<Phase, double, boost::multiplicative2<Phase, double> > > {

private:
	std::vector<Body*> bodies;

public:
	Phase();
	Phase(int size);

	int size() const;
	void resize(int size);

	int addBody(Body* body);
	std::vector<Body*> getBodies();

	void clearForces() const;
	void devideForcesByMass() const;

	Phase& operator+=(const Phase& p);
	Phase& operator*=(const double a);

	static void copyVelocitiesToPositions(const Phase& source, Phase& target);
	static void copyForcesToVelocities(const Phase& source, Phase& target);

private:
	friend std::ostream& operator<<(std::ostream &out, const Phase &phase);
};

// Only required for steppers with error control
Phase operator/(const Phase &p1, const Phase &p2);
Phase abs(const Phase &p);

// Phase bindings
namespace boost {
namespace numeric {
namespace odeint {

// declare resizeability
template<>
struct is_resizeable<Phase> {
	typedef boost::true_type type;
	const static bool value = type::value;
};

// define how to check size
template<>
struct same_size_impl<Phase, Phase> {
	static bool same_size(const Phase &v1, const Phase &v2) {
		return v1.size() == v2.size();
	}
};

// define how to resize
template<>
struct resize_impl<Phase, Phase> {
	static void resize(Phase &v1, const Phase &v2) {
		v1.resize(v2.size());
	}
};

// Specialization of vector_space_reduce, only required for steppers with error control
template<>
struct vector_space_reduce<Phase> {
	template<class Value, class Op>
	Value operator()(const Phase &p, Op op, Value init) {
		//init = op( init , p.x );
		//std::cout << init << " ";
		//init = op( init , p.y );
		//std::cout << init << " ";
		//init = op( init , p.z );
		//std::cout << init << std::endl;
		return init;
	}
};

}
}
}

#endif // PHASE_HPP
