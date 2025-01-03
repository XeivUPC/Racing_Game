#pragma once

#include "Pilot.h"
#include <string>

class Vehicle;
class Module;
class Vector2;

class PilotCPU : public Pilot
{
public:
	PilotCPU(Module* moduleAt, std::string vehicleType);
	~PilotCPU();
	update_status Update();
	void Brain();

private:
	Vector2 direction;
};
