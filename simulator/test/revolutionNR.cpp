#include <fstream>

#include "../body.hpp"
#include "../interactions/gravity.hpp"
#include "../phase.hpp"
#include "../system.hpp"

System bbsystem;
Body *earth, *moon, *iss, *apollo;

std::ofstream stream;

Phase F1(4), F2(4), F3(4), F4(4);
Phase xtemp(4);

void rungeKutta4(Phase &x, double t, double tau, System &sys) {

	//* Evaluate F1 = f(x,t).
	sys.derive(x, F1, t);

	//* Evaluate F2 = f( x+tau*F1/2, t+tau/2 ).
	double half_tau = 0.5 * tau;
	double t_half = t + half_tau;

	xtemp = x + half_tau * F1;
	sys.derive(xtemp, F2, t_half);

	//* Evaluate F3 = f( x+tau*F2/2, t+tau/2 ).
	xtemp = x + half_tau * F2;
	sys.derive(xtemp, F3, t_half);

	//* Evaluate F4 = f( x+tau*F3, t+tau ).
	double t_full = t + tau;
	xtemp = x + tau * F3;
	sys.derive(xtemp, F4, t_full);

	//* Return x(t+tau) computed from fourth-order R-K.
	x += tau / 6. * (F1 + F4 + 2. * (F2 + F3));

}

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

	double t = 0.0;
	for (int i = 0; i < 3000000; i++) {
		rungeKutta4(*bbsystem.getPhase(), t, 0.000001, bbsystem);
		t += 0.000001;
	}

	stream.close();
	std::cout << "E=" << bbsystem.getEnergy() << std::endl;

	return 0;
}
