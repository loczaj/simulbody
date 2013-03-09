#include <iostream>
#include <vector>
#include <boost/numeric/odeint.hpp>

#include "interaction.hpp"

class system {

public:

	int registerBody(Body* body);
	int registerInteraction(Interaction* interaction);

	void operator()(const state_type &x, state_type &dxdt, const double t) {
	}
};
