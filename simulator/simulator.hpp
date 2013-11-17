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

	boost::function<void(const Phase&, const double&)> observer = null_observer();

public:
	Simulator(StepperT stepper, System* sys)
			: stepper(stepper), bbsystem(sys) {
	}

	void setPrinter(const Printer &printer) {
		this->observer = printer;
	}

	void operator()(const Phase &x, Phase &dxdt, const double t) {
		bbsystem->derive(x, dxdt, t);
	}

	int simulate(double startTime, double endTime, double dt) {
		return integrate_adaptive(stepper, *this, bbsystem->phase, startTime, endTime, dt, observer);
	}

	int simulate(double startTime, double checkConditionTime, double dt, const Condition &stopCondition,
			int maxPasses = 100) {
		return 0;
	}

};

#endif /* SIMULATOR_HPP */
