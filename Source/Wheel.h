#pragma once
#include "Vehicle.h"

class PhysBody;

class Wheel
{
public:
	Wheel(Vehicle* owner);
	~Wheel();
	update_status Update();
	bool CleanUp();


	void Turn(int direction);
	void Move(int direction);
	void SetUpWheelCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse);
	void StartBrake();
	void StopBrake();


	PhysBody* body = nullptr;
private:

	void UpdateTraction();
	void UpdateFriction();
	Vector2 GetLateralVelocity();
	Vector2 GetForwardVelocity();


	Vehicle* owner=nullptr;

	float maxForwardSpeed=0;
	float maxBackwardSpeed = 0;
	float maxDriveForce = 0;
	float maxLateralImpulse = 0;

	float currentTraction=1;

	bool isBraking = false;


protected:
};

