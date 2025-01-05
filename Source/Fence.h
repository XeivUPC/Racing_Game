#pragma once
#include "BreakableObstacle.h"
#include "MapObject.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class Fence : public BreakableObstacle
{
public:
	Fence(Module* moduleAt, Vector2 position);
	~Fence() {}

	update_status Update();
	bool Render();
	bool CleanUp();

private:
	Texture2D* fenceTexture = nullptr;
	Rectangle  fenceTextureRec = { 0, 0, 47, 63 };
};