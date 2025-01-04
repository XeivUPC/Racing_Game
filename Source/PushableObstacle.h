#include "Obstacle.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class PushableObstacle : public Obstacle
{
public:
	PushableObstacle(Module* moduleAt, Vector2 position);
	~PushableObstacle() {}

	bool CleanUp();

private:
	void OnHit();

	PhysBody* body = nullptr;
	CollisionSensor sensor;

	float linearDamping = 2;
	float angularDamping = 1; 
};