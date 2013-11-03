#include <fstream>
#include <boost/numeric/odeint.hpp>

#include "../system.hpp"
#include "../interactions/gravity.hpp"

System bbsystem;
sizeT earth, iss, moon, apollo;
std::ofstream stream;

void rhs(const Phase &x, Phase &dxdt, const double t) {
	bbsystem.derive(x, dxdt, t);
}

struct write_state {
	void operator()(const Phase &x, double &t) const {
		vector3D e = x.getBodyPosition(earth);
		vector3D m = x.getBodyPosition(moon);
		vector3D i = x.getBodyPosition(iss);
		vector3D a = x.getBodyPosition(apollo);

		stream << e.x << "\t" << e.y << "\t" << m.x << "\t" << m.y << "\t";
		stream << i.x << "\t" << i.y << "\t" << a.x << "\t" << a.y << "\n";
	}
};

using namespace boost::numeric::odeint;

int main(int argc, char* atgv[]) {
	bbsystem = System();

	earth = bbsystem.createBody(5.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));
	moon = bbsystem.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 2.0, 0.0));
	iss = bbsystem.createBody(0.001, vector3D(0.2, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));
	apollo = bbsystem.createBody(0.001, vector3D(1.1, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));

	Interaction* gravityEM = new GravitationalInteraction(5, earth, moon);
	Interaction* gravityEI = new GravitationalInteraction(0.005, earth, iss);
	Interaction* gravityEA = new GravitationalInteraction(0.005, earth, apollo);
	Interaction* gravityMA = new GravitationalInteraction(0.001, moon, apollo);
	Interaction* gravityMI = new GravitationalInteraction(0.0001, moon, iss);
	Interaction* gravityIA = new GravitationalInteraction(0.000001, iss, apollo);

	bbsystem << gravityEM << gravityEI << gravityEA << gravityMA << gravityMI << gravityIA;

	stream.open("orbits.csv", std::ofstream::out);
	//double E = earth->getKineticEnergy() + moon->getKineticEnergy() + gravityEM->getEnergy();
	//std::cout << "E=" << E << std::endl;

	runge_kutta4_classic<Phase, double, Phase, double, range_algebra> stepper;
	int steps = integrate_const(stepper, rhs, bbsystem.phase, 0.0, 2.4, 0.001, write_state());

	stream.close();
	//E = earth->getKineticEnergy() + moon->getKineticEnergy() + gravityEM->getEnergy();
	//std::cout << "E=" << E << std::endl;

	return steps;
}
