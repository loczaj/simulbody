#include <fstream>
#include <boost/numeric/odeint.hpp>

#include "../system.hpp"
#include "../plotter.hpp"
#include "../interactions/coulomb.hpp"

System bbsystem;

void rhs(const Phase &x, Phase &dxdt, const double t) {
	bbsystem.derive(x, dxdt, t);
}

using namespace boost::numeric::odeint;

int main(int argc, char* atgv[]) {
	bbsystem = System();

	sizeT proton = bbsystem.createBody(1836.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 0.0, 0.0));
	sizeT electron = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));

	bbsystem.convertToCenterOfMassSystem();

	Interaction* coulomb = new CoulombInteraction(-1.0, proton, electron);
	bbsystem.addInteraction(coulomb);

	std::ofstream stream;
	std::cout.precision(10);
	stream.open("orbits.csv", std::ofstream::out);

	Printer print(stream);
	print.addField(new BodyPrintField(proton, { Coord::x, Coord::y }));
	print.addField(new BodyPrintField(electron, { Coord::x, Coord::y }));

	std::cout << "E0=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "p0=" << bbsystem.getSystemImpulse().abs() << std::endl;

	runge_kutta4_classic<Phase, double, Phase, double, range_algebra> stepper;
	int steps = integrate_const(stepper, rhs, bbsystem.phase, 0.0, 10.0, 0.001, print);

	std::cout << "En=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "pN=" << bbsystem.getSystemImpulse().abs() << std::endl;
	std::cout << "N=" << steps << std::endl;

	stream.close();

	return 0;
}
