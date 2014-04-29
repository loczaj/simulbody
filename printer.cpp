#include "printer.hpp"

namespace simulbody {

// *** Printer *** //
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

// *** BodyPrintField ***
BodyPrintField::BodyPrintField(identifier body, std::initializer_list<Coord> coords)
		: body(body) {
	for (Coord c : coords) {
		coordinates.push_back(c);
	}
}

void BodyPrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
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

// *** PositionPrintField ***
void PositionPrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
	for (identifier body = 0; body < phase.getNumberOfBodies(); body++) {

		vector3D r = phase.getBodyPosition(body);
		stream << r.x << "\t" << r.y << "\t" << r.z;

		if (body < phase.getNumberOfBodies() - 1)
			stream << "\t";
	}
}

// *** TimePrintField ***
void TimePrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
	stream << time;
}

// *** DistancePrintField ***
DistancePrintField::DistancePrintField(identifier earth, identifier moon)
		: earth(earth), moon(moon) {
}

void DistancePrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
	stream << phase.getBodyPosition(earth).distance(phase.getBodyPosition(moon));
}

// *** ConditionPrintField ***
ConditionPrintField::ConditionPrintField(Condition* condition)
		: condition(condition) {
}

void ConditionPrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
	if (condition->evaluate(phase, time)) {
		stream << "1";
	} else {
		stream << "0";
	}
}

// *** InteractionPrintField ***
InteractionPrintField::InteractionPrintField(Interaction* interaction, InteractionAttribute attribute)
		: interaction(interaction), attribute(attribute) {
}

void InteractionPrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
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

// *** CustomPrintField ***
CustomPrintField::CustomPrintField(boost::function<void(const Phase, const double, std::ostream&)> writer)
		: writer(writer) {
}

void CustomPrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
	writer(phase, time, stream);
}

// *** EmptyPrintField ***
void EmptyPrintField::writeField(const Phase &phase, const double &time, std::ostream &stream) {
}

} /* NAMESPACE SIMULBODY */
