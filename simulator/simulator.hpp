#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "system.hpp"

enum class NumericalMethod {
	adams_bashforth_moulton,
	runge_kutta4,
	runge_kutta_dopri5,
	runge_kutta_fehlberg78,
	symplectic_rkn_sb3a_mclachlan
};

class Simulator {

public:
	Simulator();

	void setSystem(System* system);
	void setNumericalMethod(NumericalMethod method);

	void addStopCondition();
	void addPlotter();

	int simulate(double startTime, double endTime, double deltaTime);
	int simulateControlled(double startTime, double endTime, double deltaTime, double tolerance);

};

#endif /* SIMULATOR_HPP */
