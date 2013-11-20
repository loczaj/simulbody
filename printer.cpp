#include "printer.hpp"

namespace simulbody {

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

} /* NAMESPACE SIMULBODY */
