#pragma once
#include "Pilot.h"
#include <string>

class Vehicle;
class Module;
class Vector2;

class Player : public Pilot
{
public:
	Player(Module* moduleat, std::string vehicleType);
	~Player();
	bool Update();
};