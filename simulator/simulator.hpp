#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <boost/numeric/odeint.hpp>

#include "condition.hpp"
#include "printer.hpp"
#include "system.hpp"

using namespace boost::numeric::odeint;

bool less_with_sign(double t1, double t2, double dt) {
	if (dt > 0)
		return t1 < t2;
	else
		return t1 > t2;
}

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

	int simulate(double startTime, double endTime, double dt) {
		return integrate_adaptive(stepper, *this, bbsystem->phase, startTime, endTime, dt);
	}

	int simulateAdaptive(double startTime, double endTime, double dt) {

//				double time = startTime;
//				size_t steps = static_cast<size_t>((endTime - startTime) / dt);
//				for (size_t step = 0; step < steps; ++step) {
//					stepper.do_step(*this, bbsystem->phase, time, dt);
//					// direct computation of the time avoids error propagation happening when using time += dt
//					// we need clumsy type analysis to get boost units working here
//					//time = startTime + static_cast< typename unit_value_type<Time>::type >( step+1 ) * dt;
//					time += dt;
//				}
//				return steps;

		typename unwrap_reference<Printer>::type &obs = *printer;
		Phase &state = bbsystem->phase;
		Simulator &simu = *this;

		const size_t max_attempts = 1000;
		const char *error_string =
				"Integrate adaptive : Maximal number of iterations reached. A step size could not be found.";
		size_t count = 0;
		while (less_with_sign(startTime, endTime, dt)) {
			// obs(state, startTime);
			if (less_with_sign(endTime, startTime + dt, dt)) {
				dt = endTime - startTime;
			}

			size_t trials = 0;
			controlled_step_result res = success;
			do {
				res = stepper.try_step(simu, state, startTime, dt);
				++trials;
			} while ((res == fail) && (trials < max_attempts));
			if (trials == max_attempts)
				throw std::overflow_error(error_string);

			++count;
		}
		// obs(state, startTime);
		return count;

	}

};

#endif /* SIMULATOR_HPP */
