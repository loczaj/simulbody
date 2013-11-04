#include <fstream>
#include <boost/numeric/odeint.hpp>

#include "../system.hpp"
#include "../interactions/coulomb.hpp"

System bbsystem;
sizeT proton, electron;
std::ofstream stream;

void rhs(const Phase &x, Phase &dxdt, const double t) {
	bbsystem.derive(x, dxdt, t);
}

struct write_state {
	void operator()(const Phase &x, double &t) const {
		vector3D p = x.getBodyPosition(proton);
		vector3D e = x.getBodyPosition(electron);

		stream << p.x << "\t" << p.y << "\t" << e.x << "\t" << e.y << std::endl;
	}
};

using namespace boost::numeric::odeint;

int main(int argc, char* atgv[]) {
	bbsystem = System();

	proton = bbsystem.createBody(1836.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 0.0, 0.0));
	electron = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));

	bbsystem.convertToCenterOfMassSystem();

	Interaction* coulomb = new CoulombInteraction(-1.0, proton, electron);
	bbsystem.addInteraction(coulomb);

	std::cout.precision(10);
	stream.open("orbits.csv", std::ofstream::out);
	std::cout << "E0=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "p0=" << bbsystem.getSystemImpulse().abs() << std::endl;

	runge_kutta4_classic<Phase, double, Phase, double, range_algebra> stepper;
	int steps = integrate_const(stepper, rhs, bbsystem.phase, 0.0, 10.0, 0.001, write_state());

	stream.close();
	std::cout << "En=" << bbsystem.getSystemEnergy() << "\t";
	std::cout << "pN=" << bbsystem.getSystemImpulse().abs() << std::endl;
	std::cout << "N=" << steps << std::endl;

	return 0;
}
