#pragma once
#include "FixedObstacle.h"
#include "MapObject.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class RockObstacle : public FixedObstacle
{
public:
	RockObstacle(Module* moduleAt, Vector2 position);
	~RockObstacle() {}

	update_status Update();
	bool Render();
	bool CleanUp();

private:
	Texture2D* rockTexture = nullptr;
	Rectangle  rockTextureRec = { 0, 63, 15, 16 };
};