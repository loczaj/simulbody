#include <fstream>
#include <boost/numeric/odeint.hpp>

#include "../system.hpp"
#include "../plotter.hpp"
#include "../interactions/gravity.hpp"

System bbsystem;

void rhs(const Phase &x, Phase &dxdt, const double t) {
	bbsystem.derive(x, dxdt, t);
}

using namespace boost::numeric::odeint;

int main(int argc, char* atgv[]) {
	bbsystem = System();

	sizeT earth = bbsystem.createBody(5.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));
	sizeT moon = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 2.0, 0.0));
	sizeT iss = bbsystem.createBody(0.001, vector3D(0.2, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));
	sizeT apollo = bbsystem.createBody(0.001, vector3D(1.1, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));

	bbsystem.convertToCenterOfMassSystem();

	Interaction* gravityEM = new GravitationalInteraction(1, earth, moon);
	Interaction* gravityEI = new GravitationalInteraction(0.001, earth, iss);
	Interaction* gravityEA = new GravitationalInteraction(0.001, earth, apollo);
	Interaction* gravityMA = new GravitationalInteraction(0.0002, moon, apollo);
	Interaction* gravityMI = new GravitationalInteraction(0.00002, moon, iss);
	Interaction* gravityIA = new GravitationalInteraction(0.0000002, iss, apollo);

	bbsystem << gravityEM << gravityEI << gravityEA << gravityMA << gravityMI << gravityIA;

	std::ofstream stream;
	stream.open("orbits.csv", std::ofstream::out);

	Plotter plot(stream);
	plot.addField(*new BodyPlotField(earth, { Coord::x, Coord::y }));
	plot.addField(*new BodyPlotField(moon, { Coord::x, Coord::y }));
	plot.addField(*new BodyPlotField(iss, { Coord::x, Coord::y }));
	plot.addField(*new BodyPlotField(apollo, { Coord::x, Coord::y }));

	std::cout << "E0=" << bbsystem.getSystemEnergy() << std::endl;

	runge_kutta4_classic<Phase, double, Phase, double, range_algebra> stepper;
	int steps = integrate_const(stepper, rhs, bbsystem.phase, 0.0, 10.0, 0.001, plot);

	stream.close();
	std::cout << "En=" << bbsystem.getSystemEnergy() << std::endl;
	std::cout << "N=" << steps << std::endl;

	return 0;
}
