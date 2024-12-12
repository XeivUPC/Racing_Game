#pragma once
#include "Vehicle.h"

class PhysBody;
class PhysJoint;

class Wheel
{
public:
	Wheel(Vehicle* owner, float radius = 0.5f, float width = 0.5f);
	~Wheel();
	update_status Update();
	bool CleanUp();

	void InstallJoint(PhysJoint* joint);
	PhysJoint* GetJoint();

	void Turn(int direction);
	void Move(int direction);
	void SetUpWheelCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse);
	Vector2 GetForwardVelocity();
	Vector2 GetLateralVelocity();

	PhysBody* body = nullptr;
	PhysJoint* joint = nullptr;
private:

	void UpdateTraction();
	void UpdateFriction();


	Vehicle* owner=nullptr;

	float maxForwardSpeed=0;
	float maxBackwardSpeed = 0;
	float maxDriveForce = 0;
	float maxLateralImpulse = 0;

	float currentTraction=5;

protected:
};

