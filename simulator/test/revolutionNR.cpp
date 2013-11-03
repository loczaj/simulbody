#include <fstream>

#include "../phase.hpp"
#include "../system.hpp"
#include "../interactions/gravity.hpp"

System bbsystem;
size_t earth, iss, moon, apollo;

std::ofstream stream;

Phase F1(4), F2(4), F3(4), F4(4);
Phase xtemp(4);

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
	bbsystem = System();

	earth = bbsystem.phase.createBody(5.0, vector3D(0.0, 0.0, 0.0), vector3D(0.0, 1.0, 0.0));
	moon = bbsystem.phase.createBody(1.0, vector3D(1.0, 0.0, 0.0), vector3D(0.0, 2.0, 0.0));
	iss = bbsystem.phase.createBody(0.001, vector3D(0.2, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));
	apollo = bbsystem.phase.createBody(0.001, vector3D(1.1, 0.0, 0.0), vector3D(0.0, 3.5, 0.0));

	Interaction* gravityEM = new GravitationalInteraction(5, earth, moon);
	Interaction* gravityEI = new GravitationalInteraction(0.005, earth, iss);
	Interaction* gravityEA = new GravitationalInteraction(0.005, earth, apollo);
	Interaction* gravityMA = new GravitationalInteraction(0.001, moon, apollo);
	Interaction* gravityMI = new GravitationalInteraction(0.0001, moon, iss);
	Interaction* gravityIA = new GravitationalInteraction(0.000001, iss, apollo);

	bbsystem << gravityEM << gravityEI << gravityEA << gravityMA << gravityMI << gravityIA;

	stream.open("orbits.csv", std::ofstream::out);
	// std::cout << "E=" << bbsystem.getEnergy() << std::endl;

	double t = 0.0;
	write_state writer;
	while (t < 2.4) {
		rungeKutta4(bbsystem.phase, t, 0.000001, bbsystem);
		writer(bbsystem.phase, t);
		t += 0.000001;
	}

	stream.close();
	// std::cout << "E=" << bbsystem.getEnergy() << std::endl;

	return 0;
}
