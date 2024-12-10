#include "Vehicle.h"
#include "Wheel.h"
#include "ModulePhysics.h"

Vehicle::Vehicle(ModuleGame* gameAt) : MapObject(gameAt)
{
}

Vehicle::~Vehicle()
{
}

update_status Vehicle::Update()
{
	for (const auto& wheel : wheels)
	{
		/// Update Wheels
		wheel->Update();
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
