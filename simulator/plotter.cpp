#include "plotter.hpp"

// Plotter

Plotter::Plotter(std::ostream &stream)
		: stream(&stream) {
}

void Plotter::addField(PlotField* field) {
	fields.push_back(field);
}

void Plotter::operator()(const Phase& p, double t) {
	for (sizeT i = 0; i < fields.size(); i++) {
		fields[i]->writeField(p, t, *stream);

		if (i < fields.size() - 1)
			*stream << "\t";
	}
	*stream << std::endl;
}

// Fields

BodyPlotField::BodyPlotField(sizeT body, std::initializer_list<Coord> coords)
		: body(body) {
	for (Coord c : coords) {
		coordinates.push_back(c);
	}
}

void BodyPlotField::writeField(const Phase &p, const double &t, std::ostream &s) {
	for (sizeT i = 0; i < coordinates.size(); i++) {

		switch (coordinates[i]) {
		case Coord::x:
			s << p.getBodyPosition(body).x;
			break;
		case Coord::y:
			s << p.getBodyPosition(body).y;
			break;
		case Coord::z:
			s << p.getBodyPosition(body).z;
			break;
		case Coord::vx:
			s << p.getBodyVelocity(body).x;
			break;
		case Coord::vy:
			s << p.getBodyVelocity(body).y;
			break;
		case Coord::vz:
			s << p.getBodyVelocity(body).z;
		}

		if (i < coordinates.size() - 1)
			s << "\t";
	}
}
