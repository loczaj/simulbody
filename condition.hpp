#ifndef CONDITION_HPP
#define CONDITION_HPP

#include "phase.hpp"

class Condition {
public:
	virtual bool evaluate(const Phase &phase, const double &time) const = 0;
	virtual ~Condition() {
	}
};

class DistanceCondition: public Condition {
private:
	identifier earth;
	identifier moon = -1;
	vector3D reference;
	double distance;

public:
	DistanceCondition(identifier earth, identifier moon, double distance)
			: earth(earth), moon(moon), distance(distance) {
	}

	DistanceCondition(identifier body, vector3D reference, double distance)
			: earth(body), reference(reference), distance(distance) {
	}

	virtual bool evaluate(const Phase &phase, const double &time) const override {
		if (moon < 0) {
			return phase.getBodyPosition(earth).distance(reference) > distance;
		} else {
			return phase.getBodyPosition(earth).distance(phase.getBodyPosition(moon)) > distance;
		}
	}
};

#endif /* CONDITION_HPP */
