#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <boost/numeric/odeint.hpp>

#include "phase.hpp"
#include "interaction.hpp"
#include "condition.hpp"
#include "printer.hpp"
#include "system.hpp"
#include "interactions/coulomb.hpp"
#include "interactions/gravity.hpp"

using namespace boost::numeric::odeint;

namespace simulbody {

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

	double simulate(double startTime, double roundTime, double dt, const Condition &stopCondition,
			int maxRounds = 100) {
		for (int i = 0; i < maxRounds; i++) {
			if (stopCondition.evaluate(bbsystem->phase, startTime)) {
				return startTime;
			}
			integrate_adaptive(stepper, *this, bbsystem->phase, startTime, startTime + roundTime, dt,
					observer);
			startTime += roundTime;
		}

		return startTime - (maxRounds + 1) * roundTime;
	}

};

} /* NAMESPACE SIMULBODY */

#endif /* SIMULATOR_HPP */