#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"
#include <vector>

using namespace std;

class MapLapSensorController;

class MapLapSensor : public MapObject {
public:
	MapLapSensor(Module* moduleAt, Vector2 position, vector<Vector2> vertices, int order);
	~MapLapSensor();

	update_status Update();
	bool CleanUp();

	void Enable();
	void Disable();
	void AddController(MapLapSensorController* lapcontroller);
	int GetOrder() const;

private:

	// Enabled determines wether the sensor can be interacted with
	bool enabled = false;
	// Activated determines wether the sensor has been triggered
	bool activated = false;

	PhysBody* body = nullptr;
	MapLapSensorController* controller;
	CollisionSensor sensor;

	int order = -1;
};