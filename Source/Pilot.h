#pragma once
#include <string>
#include "MapObject.h"

class Module;
class Vehicle;
class Vector2;

class Pilot : public MapObject
{
protected:
	int lap=0;
	int checkpoint=0;
	Vehicle* vehicle;
public:
	Pilot(Module* moduleAt, std::string vehicleType);
	~Pilot();
	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

	void AddLap();
	void AddCheckpoint();
	Vector2 GetVehiclePosition();
	void SetVehicleRotation(double angle);
	void SetVehiclePosition(Vector2 pos);
	int CurrentCheckpoint();
	int CurrentLap();
};