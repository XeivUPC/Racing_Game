#include "PilotCPU.h"
#include "Vehicle.h"
#include "Module.h"
#include <string>

PilotCPU::PilotCPU(Module* moduleAt, std::string vehicleType) : Pilot(moduleAt, vehicleType)
{
}

PilotCPU::~PilotCPU()
{
}

update_status PilotCPU::Update()
{
	Brain();
	vehicle->SetInput(direction);
	vehicle->Update();

	return UPDATE_CONTINUE;
}

void PilotCPU::Brain()
{

}
