#include <fstream>
#include <boost/numeric/odeint.hpp>

#include "../system.hpp"
#include "../simulator.hpp"
#include "../printer.hpp"
#include "../condition.hpp"
#include "../interactions/gravity.hpp"

using namespace simulbody;

int main(int argc, char* atgv[]) {
	System bbsystem;

	identifier earth = bbsystem.createBody(5.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));
	identifier moon = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 2.0, 0.0));
	identifier iss = bbsystem.createBody(0.001, vector3D(0.2, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));
	identifier apollo = bbsystem.createBody(0.001, vector3D(1.1, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));

	bbsystem.convertToCenterOfMassSystem();

	Interaction* gravityEM = new GravitationalInteraction(1, earth, moon);
	Interaction* gravityEI = new GravitationalInteraction(0.001, earth, iss);
	Interaction* gravityEA = new GravitationalInteraction(0.001, earth, apollo);
	Interaction* gravityMA = new GravitationalInteraction(0.0002, moon, apollo);
	Interaction* gravityMI = new GravitationalInteraction(0.00002, moon, iss);
	Interaction* gravityIA = new GravitationalInteraction(0.0000002, iss, apollo);

	bbsystem << gravityEM << gravityEI << gravityEA << gravityMA << gravityMI << gravityIA;

	DistanceCondition condEA(earth, apollo, 1.0);
	DistanceCondition condMI(moon, iss, 1.0);

	Printer print("orbits.csv");
	print.addField(new BodyPrintField(earth, { Coord::x, Coord::y }));
	print.addField(new BodyPrintField(moon, { Coord::x, Coord::y }));
	print.addField(new BodyPrintField(iss, { Coord::x, Coord::y }));
	print.addField(new BodyPrintField(apollo, { Coord::x, Coord::y }));
	print.addField(new DistancePrintField(earth, apollo));
	print.addField(new ConditionPrintField(&condEA));
	print.addField(new DistancePrintField(moon, iss));
	print.addField(new TimePrintField());

	std::cout.precision(10);
	std::cout << "E0=" << bbsystem.getSystemEnergy() << std::endl;

	runge_kutta4_classic<Phase> stepper;
	//auto cstepper = make_controlled(1e-20, 1e-20, stepper);
	Simulator<decltype(stepper)> simulator(stepper, &bbsystem);
	simulator.setPrinter(print);

	double stopTime = simulator.simulate(0.0, 1.0, 0.001, condMI);

	std::cout << "En=" << bbsystem.getSystemEnergy() << std::endl;
	std::cout << "t=" << stopTime << std::endl;

	return 0;
}
