#include "MapObject.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class Obstacle : public MapObject
{
public:
	Obstacle(Module* moduleAt, Vector2 position);
	~Obstacle(){}

	update_status Update();
	bool CleanUp();

	void Enable();
	void Disable();

	void Activate();
	void Deactivate();

	Vector2 GetPos();
	double GetRotation();

private:

	void OnTrigger();

	// Enabled determines wether the sensor can be interacted with
	bool enabled = false;
	// Activated determines wether the sensor has been triggered
	bool activated = false;

	PhysBody* body = nullptr;
	CollisionSensor sensor;
};