#include <boost/numeric/odeint.hpp>

#include "system.hpp"

System::System() {
	phase = Phase();
}

int System::registerBody(Body* body) {
	return phase.registerBody(body);
}

int System::registerInteraction(Interaction* interaction) {
	interactions.push_back(interaction);
	return interactions.size() - 1;
}

void System::operator ()(const Phase& x, Phase& dxdt, const double t) {

}
