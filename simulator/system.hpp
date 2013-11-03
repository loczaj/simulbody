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

	size_t createBody(double mass);
	size_t createBody(double mass, vector3D position, vector3D velocity);

	double getBodyMass(size_t body) const;
	vector3D getBodyPosition(size_t body) const;
	vector3D getBodyVelocity(size_t body) const;

	void setBodyMass(size_t body, double mass);
	void setBodyPosition(size_t body, vector3D position);
	void setBodyVelocity(size_t body, vector3D velocity);

	void addInteraction(Interaction *interaction);

	double getEnergy();

	void derive(const Phase &x, Phase &dxdt, const double t) const;

	System& operator<<(Interaction *interaction);
};

#endif // SYSTEM_HPP
