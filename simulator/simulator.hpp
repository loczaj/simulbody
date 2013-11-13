#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <boost/numeric/odeint.hpp>
#include <type_traits>

#include "system.hpp"
#include "condition.hpp"
#include "printer.hpp"

using namespace boost::numeric::odeint;
namespace pl = std::placeholders;

enum class NumericalMethod {
	adams_bashforth_moulton,
	runge_kutta4,
	runge_kutta_dopri5,
	runge_kutta_fehlberg78,
	symplectic_rkn_sb3a_mclachlan
};

extern void rhs(const Phase &x, Phase &dxdt, const double t);
template<class stepperT>
class Simulator {
private:

	stepperT step;

	NumericalMethod method = NumericalMethod::runge_kutta4;

	adams_bashforth_moulton<5, Phase> stepperABM;
	runge_kutta4_classic<Phase> stepperRK4;
	runge_kutta_dopri5<Phase> stepperRKD5;
	runge_kutta_fehlberg78<Phase> stepperRKF78;
	symplectic_rkn_sb3a_mclachlan<Phase> stepperSRSM;

	controlled_runge_kutta<runge_kutta_dopri5<Phase>, default_error_checker<double> > stepperControlledRKD5;
	controlled_runge_kutta<runge_kutta_fehlberg78<Phase>, default_error_checker<double> > stepperControlledRKF78;

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

	void setErrorTolerance(double absoluteError, double relativeError);

	int simulate(double startTime, double endTime, double deltaTime) {
		int steps = integrate_const(step, std::bind(&System::derive, *system, pl::_1, pl::_2, pl::_3),
				system->phase, startTime, endTime, deltaTime, *printer);
		return steps;
	}

	int simulateAdaptive(double startTime, double endTime, double deltaTime);

};

#endif /* SIMULATOR_HPP */
