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

	identifier createBody(double mass);
	identifier createBody(double mass, vector3D position, vector3D velocity);
	sizeT getNumberOfBodies() const;

	double getBodyMass(identifier body) const;
	double getBodyKineticEnergy(identifier body) const;
	double getBodyKineticEnergyReferenced(identifier body, identifier reference) const;
	double getBodyPotentialEnergy(identifier body) const;
	double getPairPotentialEnergy(identifier earth, identifier moon) const;
	vector3D getBodyPosition(identifier body) const;
	vector3D getBodyVelocity(identifier body) const;
	vector3D getBodyImpulse(identifier body) const;

	void setBodyMass(identifier body, double mass);
	void setBodyPosition(identifier body, vector3D position);
	void setBodyVelocity(identifier body, vector3D velocity);

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
