#pragma once
#include "Vehicle.h"
#include "MapObject.h"

class PhysJoint;

class Car : public Vehicle
{
public:
	Car(ModuleGame* gameAt);
	~Car();
	update_status Update();
	bool CleanUp();
private:
	float maxForwardSpeed = 250;
	float maxBackwardSpeed = -40;
	float backTireMaxDriveForce = 300;
	float frontTireMaxDriveForce = 500;
	float backTireMaxLateralImpulse = 8.5f;
	float frontTireMaxLateralImpulse = 7.5f;

	PhysJoint* jointFrontL;
	PhysJoint* jointFrontR;

	Wheel* wheelBackR;
	Wheel* wheelBackL;
protected:

};
