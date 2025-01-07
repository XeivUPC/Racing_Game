#include "Pilot.h"
#include "Vehicle.h"


Pilot::Pilot(SceneGame* gameAt, RaceTrack* track, std::string vehicleType) : MapObject((Module*)gameAt)
{
	this->gameAt = gameAt;
	this->track = track;

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

int Pilot::CurrentCheckpoint()
{
	return checkpoint;
}

int Pilot::CurrentLap()
{
	return lap;
}

void Pilot::SetCharacterIndex(int index)
{
	characterIndex = index;
}

std::string Pilot::GetPilotName()
{
	return pilotName;
}
