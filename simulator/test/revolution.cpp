#include <boost/operators.hpp>
#include <boost/numeric/odeint.hpp>

#include <fstream>

#include "../body.hpp"
#include "../phase.hpp"
#include "../system.hpp"
#include "../interactions/coulomb.hpp"

System* bbsystem;
Body* earth;
Body* moon;
std::ofstream stream;

void rhs(const Phase &x, Phase &dxdt, const double t) {
	bbsystem->derive(x, dxdt, t);
}

struct write_state {
	void operator()(const Phase &x, double &t) const {
		stream << earth->x << "\t" << earth->y << "\t" << moon->x << "\t" << moon->y << "\n";
	}
};

using namespace boost::numeric::odeint;

int main(int argc, char* atgv[]) {
	earth = new Body(5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	moon = new Body(1.0, 1.0, 0.0, 0.0, 0.0, 2.0, 0.0);

	Interaction* gravity = new CoulombInteraction(-1.0);
	gravity->registerBodies(earth, moon);

	bbsystem = new System();
	bbsystem->registerBody(earth);
	bbsystem->registerBody(moon);
	bbsystem->registerInteraction(gravity);

	stream.open("orbits.csv", std::ofstream::out);

	runge_kutta4<Phase, double, Phase, double, vector_space_algebra> stepper;
	int steps = integrate_const(stepper, rhs, *bbsystem->getPhase(), 0.0, 3.0, 0.001,
			write_state());

	stream.close();
	return steps;
}
