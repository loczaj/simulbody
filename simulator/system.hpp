#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <utility>
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
	sizeT getNumberOfBodies() const;

	double getBodyMass(sizeT body) const;
	double getBodyKineticEnergy(sizeT body) const;
	vector3D getBodyPosition(sizeT body) const;
	vector3D getBodyVelocity(sizeT body) const;
	vector3D getBodyImpulse(sizeT body) const;

	void setBodyMass(sizeT body, double mass);
	void setBodyPosition(sizeT body, vector3D position);
	void setBodyVelocity(sizeT body, vector3D velocity);

	double getSystemMass() const;
	double getSystemEnergy() const;
	vector3D getSystemCenterOfMass() const;
	vector3D getSystemImpulse() const;

	std::pair<vector3D, vector3D> convertToCenterOfMassSystem();

	void addInteraction(Interaction *interaction);

	void derive(const Phase &x, Phase &dxdt, const double t) const;

	System& operator<<(Interaction *interaction);
};

#endif // SYSTEM_HPP
