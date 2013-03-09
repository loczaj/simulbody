#include <iostream>
#include <vector>
#include <cmath>
#include <boost/operators.hpp>
#include <boost/numeric/odeint.hpp>

#include "body.hpp"

class Phase: boost::additive1<Phase,
		boost::additive2<Phase, double, boost::multiplicative2<Phase, double> > > {

	std::vector<Body*> bodies;

public:
	Phase();

	int registerBody(Body* body);

	Phase& operator+=(const Phase &p);
	Phase& operator*=(const double a);
};

// Only required for steppers with error control
Phase operator/(const Phase &p1, const Phase &p2);
Phase abs(const Phase &p);

// Specialization of vector_space_reduce, only required for steppers with error control
namespace boost {
namespace numeric {
namespace odeint {
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
//]

// Print phase
std::ostream& operator<<(std::ostream &out, const Phase &p);
