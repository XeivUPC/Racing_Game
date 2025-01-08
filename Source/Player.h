#pragma once
#include "Pilot.h"
#include <string>

class Vehicle;
class SceneGame;
struct Vector2;

class Player : public Pilot
{
public:
	Player(SceneGame* gameAt, RaceTrack* track, std::string vehicleType, Color vehicleColor);
	~Player();
	update_status Update();
};