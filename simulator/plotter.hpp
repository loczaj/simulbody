#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <iostream>
#include <vector>
#include <initializer_list>

#include "phase.hpp"

class PlotField {
public:

	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream) = 0;
	virtual ~PlotField() {
	}
};

class BodyPlotField: public PlotField {
private:

	sizeT body;
	std::vector<Coord> coordinates;

public:
	BodyPlotField(sizeT body, std::initializer_list<Coord> coodrs);
	virtual void writeField(const Phase &phase, const double &time, std::ostream &stream);
};

class Plotter {
public:

	std::vector<PlotField*> fields;

	Plotter(std::ostream &stream);

	void addField(PlotField* field);

	void operator()(const Phase& x, double t);

private:

	std::ostream* stream;
};

#endif /* PLOTTER_HPP */
