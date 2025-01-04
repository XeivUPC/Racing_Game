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

	Vector2 GetPos();
	double GetRotation();

private:
	virtual void OnHit();
	void OnTrigger();

	PhysBody* body = nullptr;
	CollisionSensor sensor;
};