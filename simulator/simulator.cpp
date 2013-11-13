#include "simulator.hpp"

using namespace boost::numeric::odeint;

void Simulator::setSystem(System* system) {
	this->system = system;
}

void Simulator::setStopCondition(Condition* condition) {
	this->stopCondition = condition;
}

void Simulator::setPrinter(Printer* printer) {
	this->printer = printer;
}

void Simulator::setNumericalMethod(NumericalMethod method) {
	this->method = method;
}

void Simulator::setErrorTolerance(double absoluteError, double relativeError) {
	stepperControlledRKD5 = make_controlled(absoluteError, relativeError, stepperRKD5);
	stepperControlledRKF78 = make_controlled(absoluteError, relativeError, stepperRKF78);
}

int Simulator::simulate(double startTime, double endTime, double deltaTime) {
	return 0;
}
