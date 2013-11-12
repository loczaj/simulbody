#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <iostream>
#include <vector>
#include <initializer_list>

#include "phase.hpp"
#include "condition.hpp"

class PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) = 0;
	virtual ~PrintField() {
	}
};

class BodyPrintField: public PrintField {
private:
	sizeT body;
	std::vector<Coord> coordinates;

public:
	BodyPrintField(sizeT body, std::initializer_list<Coord> coords);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class ConditionPrintField: public PrintField {
private:
	Condition* condition;

public:
	ConditionPrintField(Condition* condition);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class Printer {
public:
	std::vector<PrintField*> fields;

	Printer(std::ostream &stream);

	void addField(PrintField* field);

	void operator()(const Phase& x, double t);

private:
	std::ostream* stream;
};

#endif /* PRINTER_HPP */
