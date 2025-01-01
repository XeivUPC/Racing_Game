#pragma once
#include "Pilot.h"
#include <string>

class Vehicle;
class Module;
class Vector2;

class Player : public Pilot
{
public:
	Player(Module* moduleAt, std::string vehicleType);
	~Player();
	update_status Update();
};