#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <iostream>
#include <fstream>
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
	sizeT body;
	std::vector<Coord> coordinates;

public:
	BodyPrintField(sizeT body, std::initializer_list<Coord> coords);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class TimePrintField: public PrintField {
public:
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

class ConditionPrintField: public PrintField {
	Condition* condition;

public:
	ConditionPrintField(Condition* condition);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) override;
};

#endif /* PRINTER_HPP */
