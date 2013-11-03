#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>

#include "interaction.hpp"
#include "phase.hpp"

class System {

private:

	std::vector<double> masses;
	std::vector<Interaction*> interactions;
	// TODO Add fields

public:

	Phase phase;

	sizeT createBody(double mass);
	sizeT createBody(double mass, vector3D position, vector3D velocity);

	double getBodyMass(sizeT body) const;
	vector3D getBodyPosition(sizeT body) const;
	vector3D getBodyVelocity(sizeT body) const;

	void setBodyMass(sizeT body, double mass);
	void setBodyPosition(sizeT body, vector3D position);
	void setBodyVelocity(sizeT body, vector3D velocity);

	void addInteraction(Interaction *interaction);

	double getEnergy();

	void derive(const Phase &x, Phase &dxdt, const double t) const;

	System& operator<<(Interaction *interaction);
};

#endif // SYSTEM_HPP
