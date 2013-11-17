#include "printer.hpp"

// Printer

Printer::Printer(std::string fileName) {
	fileStream = new std::ofstream(fileName, std::ofstream::out);
	stream = fileStream;
}

Printer::Printer(std::ostream &stream)
		: stream(&stream) {
}

Printer::Printer(const Printer &other) {
	fields = other.fields;
	stream = other.stream;
	fileStream = nullptr;
}

void Printer::setPrecision(int digits) {
	if (stream != nullptr)
		stream->precision(digits);
}

void Printer::addField(PrintField* field) {
	fields.push_back(field);
}

void Printer::operator()(const Phase& p, double t) {
	for (sizeT i = 0; i < fields.size(); i++) {
		fields[i]->writeField(p, t, *stream);

		if (i < fields.size() - 1)
			*stream << "\t";
	}
	*stream << std::endl;
}

Printer::~Printer() {
	if (fileStream != nullptr) {
		fileStream->close();
		delete fileStream;
		fileStream = nullptr;
	}
}

// Fields

BodyPrintField::BodyPrintField(sizeT body, std::initializer_list<Coord> coords)
		: body(body) {
	for (Coord c : coords) {
		coordinates.push_back(c);
	}
}

void BodyPrintField::writeField(const Phase &p, const double &t, std::ostream &s) {
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

void TimePrintField::writeField(const Phase &p, const double &t, std::ostream &s) {
	s << t;
}

ConditionPrintField::ConditionPrintField(Condition* condition)
		: condition(condition) {
}

void ConditionPrintField::writeField(const Phase &p, const double &t, std::ostream &s) {
	if (condition->evaluate(p, t)) {
		s << "1";
	} else {
		s << "0";
	}
}
