#include "Vehicle.h"
#include "Wheel.h"
#include "ModulePhysics.h"

Vehicle::Vehicle(Module* gameAt) : MapObject(gameAt)
{
}

Vehicle::~Vehicle()
{
}

update_status Vehicle::Update()
{
	GetInput();
	for (const auto& wheel : wheels)
	{
		wheel->Update();	
	}
	for (const auto& wheel : throttlingWheels)
	{
		wheel->Move((int)moveInput.y);
	}

	float lockAngle = 35 * DEGTORAD;
	float turnSpeedPerSec = 160 * DEGTORAD;
	float turnPerTimeStep = turnSpeedPerSec / 60.0f;
	float desiredAngle = 0;

	desiredAngle = moveInput.x * lockAngle;

	for (const auto& wheel : steeringWheels)
	{
		float angleNow = wheel->GetJoint()->GetJointAngle();
		float angleToTurn = desiredAngle - angleNow;
		angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
		float newAngle = angleNow + angleToTurn;
		wheel->GetJoint()->SetLimits(newAngle, newAngle);
	}


	return UPDATE_CONTINUE;
}

bool Vehicle::CleanUp()
{
	delete body;
	for (const auto& wheel : wheels)
	{
		/// Do Clean Up
		wheel->CleanUp();
		delete wheel;
	}
	wheels.clear();
	throttlingWheels.clear();
	steeringWheels.clear();
	return true;
}

void Vehicle::GetInput()
{
	moveInput = { 0,0 };

	if (IsKeyDown(KEY_W))
		moveInput.y += 1;
	if (IsKeyDown(KEY_S))
		moveInput.y -= 1;

	if (IsKeyDown(KEY_A))
		moveInput.x -= 1;
	if (IsKeyDown(KEY_D))
		moveInput.x += 1;
}
