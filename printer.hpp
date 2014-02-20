#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <fstream>
#include <boost/function.hpp>
#include <initializer_list>
#include <iostream>
#include <vector>

#include "phase.hpp"
#include "condition.hpp"
#include "interaction.hpp"

namespace simulbody {

// *** PrintField ***
class PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) = 0;
	virtual ~PrintField() {
	}
};

// *** Printer ***
class Printer {
	std::vector<PrintField*> fields;
	std::ostream* stream = nullptr;
	std::ofstream* fileStream = nullptr;

public:
	Printer(std::string fileName);
	Printer(std::ostream &stream);
	Printer(const Printer &other);
	Printer& operator=(const Printer &rhs) = delete;

	void setPrecision(int digits);
	void addField(PrintField* field);
	void operator()(const Phase& x, double t);
	~Printer();
};

// *** BodyPrintField ***
class BodyPrintField: public PrintField {
	identifier body;
	std::vector<Coord> coordinates;

public:
	BodyPrintField(identifier body, std::initializer_list<Coord> coords)
			: body(body) {
		for (Coord c : coords) {
			coordinates.push_back(c);
		}
	}

	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override {
		for (sizeT i = 0; i < coordinates.size(); i++) {

			switch (coordinates[i]) {
			case Coord::x:
				stream << phase.getBodyPosition(body).x;
				break;
			case Coord::y:
				stream << phase.getBodyPosition(body).y;
				break;
			case Coord::z:
				stream << phase.getBodyPosition(body).z;
				break;
			case Coord::vx:
				stream << phase.getBodyVelocity(body).x;
				break;
			case Coord::vy:
				stream << phase.getBodyVelocity(body).y;
				break;
			case Coord::vz:
				stream << phase.getBodyVelocity(body).z;
			}

			if (i < coordinates.size() - 1)
				stream << "\t";
		}
	}
};

// *** PositionPrintField ***
class PositionPrintField: public PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override {
		for (identifier body = 0; body < phase.getNumberOfBodies(); body++) {

			vector3D r = phase.getBodyPosition(body);
			stream << r.x << "\t" << r.y << "\t" << r.z;

			if (body < phase.getNumberOfBodies() - 1)
				stream << "\t";
		}
	}
};

// *** TimePrintField ***
class TimePrintField: public PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override {
		stream << time;
	}
};

// *** DistancePrintField ***
class DistancePrintField: public PrintField {
	identifier earth;
	identifier moon;

public:
	DistancePrintField(identifier earth, identifier moon)
			: earth(earth), moon(moon) {
	}

	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override {
		stream << phase.getBodyPosition(earth).distance(phase.getBodyPosition(moon));
	}
};

// *** ConditionPrintField ***
class ConditionPrintField: public PrintField {
	Condition* condition;

public:
	ConditionPrintField(Condition* condition)
			: condition(condition) {
	}

	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override {
		if (condition->evaluate(phase, time)) {
			stream << "1";
		} else {
			stream << "0";
		}
	}
};

// *** InteractionPrintField ***
enum class InteractionAttribute {
	relativePosition, relativeVelocity, energy, actingForce, actingVelocity
};

class InteractionPrintField: public PrintField {
	Interaction* interaction;
	InteractionAttribute attribute;

public:
	InteractionPrintField(Interaction* interaction, InteractionAttribute attribute)
			: interaction(interaction), attribute(attribute) {
	}

	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override {
		switch (attribute) {
		case InteractionAttribute::relativePosition:
			stream << interaction->relativePosition;
			break;
		case InteractionAttribute::relativeVelocity:
			stream << interaction->relativeVelocity;
			break;
		case InteractionAttribute::energy:
			stream << interaction->getEnergy(phase);
			break;
		case InteractionAttribute::actingForce:
			stream << interaction->actingForce;
			break;
		case InteractionAttribute::actingVelocity:
			stream << interaction->actingVelocity;
			break;
		}
	}
};

// *** CustomPrintField ***
class CustomPrintField: public PrintField {
	boost::function<void(const Phase, const double, std::ostream&)> writer;

public:
	CustomPrintField(boost::function<void(const Phase, const double, std::ostream&)> writer)
			: writer(writer) {
	}

	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override {
		writer(phase, time, stream);
	}
};

} /* NAMESPACE SIMULBODY */

#endif /* PRINTER_HPP */
