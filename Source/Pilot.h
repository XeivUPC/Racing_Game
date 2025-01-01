#pragma once
#include <string>

class Module;
class Vehicle;
class Vector2;
class CollisionSensor;

class Pilot
{
private:
	CollisionSensor sensor;
protected:
	int lap;
	int checkpoint;
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
	int CurrentCheckpoint();
};