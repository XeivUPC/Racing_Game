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
		wheel->Move((int)moveInput.y);
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
