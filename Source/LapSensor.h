#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"
#include <vector>

using namespace std;

class LapSensor : public MapObject {
public:
	LapSensor(Module* gameAt, Vector2 position, vector<Vector2> vertices, int order);
	~LapSensor();

	update_status Update();
	bool CleanUp();

	void Enable();
	void Disable();

	void Activate();
	void Deactivate();

	int GetOrder() const;

private:
	void OnTrigger();

	// Enabled determines wether the sensor can be interacted with
	bool enabled = false;
	// Activated determines wether the sensor has been triggered
	bool activated = false;

	PhysBody* body = nullptr;
	CollisionSensor sensor;

	int order = -1;
};