#pragma once
#include <string>

class Module;
class Vehicle;
class Vector2;

class Pilot
{
protected:
	int lap;
	int currentCheckpoint;
	Vehicle* vehicle;
	Module* moduleAt;
public:
	Pilot(Module* moduleat, std::string vehicleType);
	~Pilot();
	bool Start();
	virtual bool Update() = 0;
	bool Render();
	bool CleanUp();

	void AddLap();
	void AddCheckpoint();
	Vector2 GetVehiclePosition();
};