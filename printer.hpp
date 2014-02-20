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

class PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) = 0;
	virtual ~PrintField() {
	}
};

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

class BodyPrintField: public PrintField {
	identifier body;
	std::vector<Coord> coordinates;

public:
	BodyPrintField(identifier body, std::initializer_list<Coord> coords);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class PositionPrintField: public PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class TimePrintField: public PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class DistancePrintField: public PrintField {
	identifier earth;
	identifier moon;

public:
	DistancePrintField(identifier earth, identifier moon);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class ConditionPrintField: public PrintField {
	Condition* condition;

public:
	ConditionPrintField(Condition* condition);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

enum class InteractionAttribute {
	relativePosition, relativeVelocity, energy, actingForce, actingVelocity
};

class InteractionPrintField: public PrintField {
	Interaction* interaction;
	InteractionAttribute attribute;

public:
	InteractionPrintField(Interaction* interaction, InteractionAttribute attribute);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class CustomPrintField: public PrintField {
	boost::function<void(const Phase, const double, std::ostream&)> writer;

public:
	CustomPrintField(boost::function<void(const Phase, const double, std::ostream&)> writer);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

} /* NAMESPACE SIMULBODY */

#endif /* PRINTER_HPP */
