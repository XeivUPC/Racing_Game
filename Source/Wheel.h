#pragma once
#include "Vehicle.h"
#include "CollisionSensor.h"


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

	void Turn(float direction);
	void Move(float direction);
	void Render();

	void SetUpWheelCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse);
	void SetUpWheelRenderCharacteristics(Texture2D* wheelTexture, Rectangle wheelTextureRec, Color color, bool rendereable, bool rendersOverVehicle);
	void MultiplyForwardVelocity(float multiplier);
	Vector2 GetForwardVelocity();
	Vector2 GetLateralVelocity();

	PhysBody* body = nullptr;
	PhysJoint* joint = nullptr;

	bool rendersOverVehicle = false;

private:

	void UpdateTraction();
	void UpdateFriction();

	CollisionSensor sensor;
	Vehicle* owner=nullptr;
	Color wheelColor = WHITE;

	float maxForwardSpeed=0;
	float maxBackwardSpeed = 0;
	float maxDriveForce = 0;
	float maxLateralImpulse = 0;
	float forwardSpeedModification = 1;

	float currentTraction=5;

	bool rendereable=true;

	Texture2D* wheelTexture = nullptr;
	Rectangle  wheelTextureRec = {0,0,0,0};

protected:
};

