#include <fstream>

#include "../phase.hpp"
#include "../system.hpp"
#include "../printer.hpp"
#include "../interactions/gravity.hpp"

Phase F1(24), F2(24), F3(24), F4(24);
Phase xtemp(24);

void rungeKutta4(Phase &x, double t, double tau, System &sys) {

	//* Evaluate F1 = f(x,t).
	sys.derive(x, F1, t);

	//* Evaluate F2 = f( x+tau*F1/2, t+tau/2 ).
	double half_tau = 0.5 * tau;
	double t_half = t + half_tau;

	for (identifier i = 0; i < x.size(); i++)
		xtemp[i] = x[i] + half_tau * F1[i];

	sys.derive(xtemp, F2, t_half);

	//* Evaluate F3 = f( x+tau*F2/2, t+tau/2 ).
	for (identifier i = 0; i < x.size(); i++)
		xtemp[i] = x[i] + half_tau * F2[i];

	sys.derive(xtemp, F3, t_half);

	//* Evaluate F4 = f( x+tau*F3, t+tau ).
	double t_full = t + tau;

	for (identifier i = 0; i < x.size(); i++)
		xtemp[i] = x[i] + tau * F3[i];

	sys.derive(xtemp, F4, t_full);

	//* Return x(t+tau) computed from fourth-order R-K.
	for (identifier i = 0; i < x.size(); i++)
		x[i] += tau / 6. * (F1[i] + F4[i] + 2. * (F2[i] + F3[i]));

}

int main(int argc, char* atgv[]) {
	System bbsystem;

	identifier earth = bbsystem.createBody(5.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));
	identifier moon = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 2.0, 0.0));
	identifier iss = bbsystem.createBody(0.001, vector3D(0.2, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));
	identifier apollo = bbsystem.createBody(0.001, vector3D(1.1, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));

	Interaction* gravityEM = new GravitationalInteraction(5, earth, moon);
	Interaction* gravityEI = new GravitationalInteraction(0.005, earth, iss);
	Interaction* gravityEA = new GravitationalInteraction(0.005, earth, apollo);
	Interaction* gravityMA = new GravitationalInteraction(0.001, moon, apollo);
	Interaction* gravityMI = new GravitationalInteraction(0.0001, moon, iss);
	Interaction* gravityIA = new GravitationalInteraction(0.000001, iss, apollo);

	bbsystem << gravityEM << gravityEI << gravityEA << gravityMA << gravityMI << gravityIA;

	std::ofstream stream;
	stream.open("orbits.csv", std::ofstream::out);

	Printer print(stream);
	print.addField(new BodyPrintField(earth, { Coord::x, Coord::y }));
	print.addField(new BodyPrintField(moon, { Coord::x, Coord::y }));
	print.addField(new BodyPrintField(iss, { Coord::x, Coord::y }));
	print.addField(new BodyPrintField(apollo, { Coord::x, Coord::y }));

	std::cout << "E0=" << bbsystem.getSystemEnergy() << std::endl;

	double t = 0.0;
	int steps = 0;

	while (t < 2.4) {
		print(bbsystem.phase, t);
		rungeKutta4(bbsystem.phase, t, 0.001, bbsystem);
		t += 0.001;
		steps++;
	}

	stream.close();
	std::cout << "En=" << bbsystem.getSystemEnergy() << std::endl;
	std::cout << "N=" << steps << std::endl;

	return 0;
}
