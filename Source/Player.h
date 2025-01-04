#pragma once
#include "Pilot.h"
#include <string>

class Vehicle;
class SceneGame;
class Vector2;

class Player : public Pilot
{
public:
	Player(SceneGame* gameAt, RaceTrack* track, std::string vehicleType);
	~Player();
	update_status Update();
};