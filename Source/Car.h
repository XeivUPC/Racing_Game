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
	float maxBackwardSpeed = -70;
	float backTireMaxDriveForce = 250;
	float frontTireMaxDriveForce = 250;
	float backTireMaxLateralImpulse = 20.5f;
	float frontTireMaxLateralImpulse = 12.5f;

	PhysJoint* jointFrontL;
	PhysJoint* jointFrontR;

	PhysJoint* jointBackL;
	PhysJoint* jointBackR;

	Texture2D* carTexture;
	Texture2D* wheelTexture;

protected:

};
