#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <boost/numeric/odeint.hpp>
#include <functional>

#include "condition.hpp"
#include "printer.hpp"
#include "system.hpp"

using namespace boost::numeric::odeint;
namespace pl = std::placeholders;

enum class NumericalMethod {
	adams_bashforth_moulton,
	runge_kutta4,
	runge_kutta_dopri5,
	runge_kutta_fehlberg78,
	symplectic_rkn_sb3a_mclachlan
};

template<class StepperT>
class Simulator {
private:

	StepperT stepper;

	System* system = nullptr;
	Printer* printer = nullptr;
	Condition* stopCondition = nullptr;

public:

	void setSystem(System* system) {
		this->system = system;
	}
	void setStopCondition(Condition* condition) {
		this->stopCondition = condition;
	}
	void setPrinter(Printer* printer) {
		this->printer = printer;
	}

	int simulate(double startTime, double endTime, double deltaTime) {
		int steps = integrate_const(stepper, std::bind(&System::derive, *system, pl::_1, pl::_2, pl::_3),
				system->phase, startTime, endTime, deltaTime, *printer);
		return steps;
	}

	int simulateAdaptive(double startTime, double endTime, double deltaTime);

};

#endif /* SIMULATOR_HPP */
