#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"
#include <vector>

using namespace std;

class RaceTrack;

class MapLapSensor : public MapObject {
public:
	MapLapSensor(Module* moduleAt, Vector2 position, vector<Vector2> vertices, RaceTrack* track, int order);
	~MapLapSensor();

	update_status Update();
	bool CleanUp();

	void Enable();
	void Disable();
	int GetOrder() const;
	Vector2 GetCenter();
private:

	// Enabled determines wether the sensor can be interacted with
	bool enabled = false;
	// Activated determines wether the sensor has been triggered
	bool activated = false;

	PhysBody* body = nullptr;
	CollisionSensor sensor;
	RaceTrack* track;

	int order = -1;

	vector<Vector2> vertices;
};