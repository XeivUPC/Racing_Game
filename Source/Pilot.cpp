#include "Pilot.h"
#include "Vehicle.h"

Pilot::Pilot(Module* moduleat, std::string vehicleType)
{
	moduleAt = moduleat;

	vehicle = new Vehicle(moduleAt, vehicleType);
	checkpoint = 0;
	lap = 0;
}

Pilot::~Pilot()
{
}

bool Pilot::Start()
{
	return true;
}

bool Pilot::Render()
{
	vehicle->Render();
	return true;
}

bool Pilot::CleanUp()
{
	vehicle->CleanUp();
	delete vehicle;
	return true;
}

void Pilot::AddLap()
{
	lap++;
	checkpoint = 0;
}

void Pilot::AddCheckpoint()
{
	checkpoint++;
}

Vector2 Pilot::GetVehiclePosition()
{
	return vehicle->GetPhysicPosition();
}

int Pilot::CurrentCheckpoint()
{
	return checkpoint;
}

