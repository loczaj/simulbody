#include <boost/operators.hpp>
#include <boost/numeric/odeint.hpp>

#include "../body.hpp"
#include "../phase.hpp"
#include "../system.hpp"
#include "../interactions/coulomb.hpp"

System* bbsystem;

void rhs(const Phase &x, Phase &dxdt, const double t) {
	bbsystem->derive(x, dxdt, t);
}

void write(const Phase &x, const double t) {
	std::cout << x;
}

using namespace boost::numeric::odeint;

int main(int argc, char* atgv[]) {
	Body* earth = new Body(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	Body* apple = new Body(1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	Interaction* gravity = new CoulombInteraction(-1.0);
	gravity->registerBodies(earth, apple);

	bbsystem = new System();
	bbsystem->registerBody(earth);
	bbsystem->registerBody(apple);
	bbsystem->registerInteraction(gravity);

	runge_kutta4<Phase, double, Phase, double, vector_space_algebra> stepper;
	int steps = integrate_const(stepper, rhs, *bbsystem->getPhase(), 0.0, 10000.0, 0.001);

	return steps;
}
