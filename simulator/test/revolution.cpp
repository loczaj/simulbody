#include <boost/operators.hpp>
#include <boost/numeric/odeint.hpp>

#include <fstream>

#include "../body.hpp"
#include "../phase.hpp"
#include "../system.hpp"
#include "../interactions/gravity.hpp"

System bbsystem;
Body *earth, *moon, *iss, *apollo;
std::ofstream stream;

void rhs(const Phase &x, Phase &dxdt, const double t) {
	bbsystem.derive(x, dxdt, t);
}

struct write_state {
	void operator()(const Phase &x, double &t) const {
		stream << earth->x << "\t" << earth->y << "\t" << moon->x << "\t" << moon->y << "\t" << iss->x << "\t"
				<< iss->y << "\t" << apollo->x << "\t" << apollo->y << "\n";
	}
};

using namespace boost::numeric::odeint;

int main(int argc, char* atgv[]) {
	earth = new Body(5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	iss = new Body(0.001, 0.1, 0.0, 0.0, 0.0, 3.5, 0.0);
	moon = new Body(1.0, 1.0, 0.0, 0.0, 0.0, 2.0, 0.0);
	apollo = new Body(0.001, 1.1, 0.0, 0.0, 0.0, 3.5, 0.0);

	Interaction* gravityEM = new GravitationalInteraction(0.2, earth, moon);
	Interaction* gravityEI = new GravitationalInteraction(0.2, earth, iss);
	Interaction* gravityEA = new GravitationalInteraction(0.2, earth, apollo);
	Interaction* gravityMA = new GravitationalInteraction(0.2, moon, apollo);
	Interaction* gravityMI = new GravitationalInteraction(0.2, moon, iss);
	Interaction* gravityIA = new GravitationalInteraction(0.2, iss, apollo);

	bbsystem = System();
	bbsystem << earth << iss << moon << apollo;
	bbsystem << gravityEM << gravityEI << gravityEA << gravityMA << gravityMI << gravityIA;

	stream.open("orbits.csv", std::ofstream::out);
	std::cout << "E=" << bbsystem.getEnergy() << std::endl;

	runge_kutta4_classic<Phase, double, Phase, double, vector_space_algebra> stepper;
	int steps = integrate_const(stepper, rhs, *bbsystem.getPhase(), 0.0, 3.0, 0.001, write_state());

	stream.close();
	std::cout << "E=" << bbsystem.getEnergy() << std::endl;

	return steps;
}
