#pragma once
#include "Obstacle.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class FixedObstacle : public Obstacle
{
public:
	FixedObstacle(Module* moduleAt, Vector2 position, float radius);
	~FixedObstacle() {}

	update_status Update();
	bool CleanUp();

private:


protected:
	void OnHit();
};