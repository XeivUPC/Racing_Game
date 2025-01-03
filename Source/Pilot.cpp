#include "Pilot.h"
#include "Vehicle.h"


Pilot::Pilot(Module* moduleAt, std::string vehicleType) : MapObject(moduleAt)
{
	this->moduleAt = moduleAt;

	vehicle = new Vehicle(moduleAt,this, vehicleType);
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

update_status Pilot::Update()
{
	return UPDATE_CONTINUE;
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

void Pilot::SetVehiclePosition(Vector2 pos)
{
	vehicle->SetPosition(pos);
}

void Pilot::SetVehicleRotation(double angle)
{
	vehicle->SetRotation(angle);
	
}

int Pilot::CurrentCheckpoint()
{
	return checkpoint;
}

int Pilot::CurrentLap()
{
	return lap;
}

std::string Pilot::GetPilotName()
{
	return pilotName;
}
