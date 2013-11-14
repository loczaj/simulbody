#include <fstream>
#include <boost/numeric/odeint.hpp>

#include "../system.hpp"
#include "../printer.hpp"
#include "../simulator.hpp"
#include "../interactions/coulomb.hpp"

int main(int argc, char* atgv[]) {
	System bbsystem;

	sizeT proton = bbsystem.createBody(1836.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 0.0, 0.0));
	sizeT electron = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));

	bbsystem.convertToCenterOfMassSystem();

	Interaction* coulomb = new CoulombInteraction(-1.0, proton, electron);
	bbsystem.addInteraction(coulomb);

	std::ofstream stream;
	std::cout.precision(10);
	stream.open("orbits.csv", std::ofstream::out);

	Printer* printer = new Printer(stream);
	printer->addField(new BodyPrintField(proton, { Coord::x, Coord::y }));
	printer->addField(new BodyPrintField(electron, { Coord::x, Coord::y }));

	std::cout << "E0=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "p0=" << bbsystem.getSystemImpulse().abs() << std::endl;

	runge_kutta4_classic<Phase> stepper;
	Simulator<decltype(stepper)> simulator(stepper, &bbsystem);
	simulator.setPrinter(printer);

	int steps = simulator.simulate(0.0, 10.0, 0.001);

	std::cout << "En=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "pN=" << bbsystem.getSystemImpulse().abs() << std::endl;
	std::cout << "N=" << steps << std::endl;

	stream.close();

	return 0;
}
