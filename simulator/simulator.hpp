#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <boost/numeric/odeint.hpp>

#include "condition.hpp"
#include "printer.hpp"
#include "system.hpp"

using namespace boost::numeric::odeint;

template<class StepperT>
class Simulator {
private:

	StepperT stepper;
	System* bbsystem;

	Printer* printer = nullptr;
	Condition* stopCondition = nullptr;

public:
	Simulator(StepperT stepper, System* sys)
			: stepper(stepper), bbsystem(sys) {
	}

	void setStopCondition(Condition* condition) {
		this->stopCondition = condition;
	}

	void setPrinter(Printer* printer) {
		this->printer = printer;
	}

	void operator()(const Phase &x, Phase &dxdt, const double t) {
		bbsystem->derive(x, dxdt, t);
	}

	int simulate(double startTime, double endTime, double deltaTime) {
		int steps = integrate_const(stepper, *this, bbsystem->phase, startTime, endTime, deltaTime, *printer);
		return steps;
	}

	int simulateAdaptive(double startTime, double endTime, double deltaTime);

};

#endif /* SIMULATOR_HPP */
