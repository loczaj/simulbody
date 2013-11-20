#include <boost/numeric/odeint.hpp>

#include "../system.hpp"
#include "../printer.hpp"
#include "../simulator.hpp"
#include "../interactions/coulomb.hpp"

using namespace simulbody;

int main(int argc, char* atgv[]) {
	System bbsystem;

	identifier proton = bbsystem.createBody(1836.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 0.0, 0.0));
	identifier electron = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));

	bbsystem << new CoulombInteraction(-1.0, proton, electron);

	bbsystem.convertToCenterOfMassSystem();

	Printer printer("orbits.csv");
	printer.addField(new BodyPrintField(proton, { Coord::x, Coord::y }));
	printer.addField(new BodyPrintField(electron, { Coord::x, Coord::y }));

	std::cout.precision(10);
	std::cout << "E0=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "p0=" << bbsystem.getSystemImpulse().abs() << std::endl;

	runge_kutta4_classic<Phase> stepper;
	Simulator<decltype(stepper)> simulator(stepper, &bbsystem);
	simulator.setPrinter(printer);

	int steps = simulator.simulate(0.0, 10.0, 0.001);

	std::cout << "En=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "pN=" << bbsystem.getSystemImpulse().abs() << std::endl;
	std::cout << "N=" << steps << std::endl;

	return 0;
}
