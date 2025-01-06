#pragma once
#include "BreakableObstacle.h"
#include "MapObject.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class FenceObstacle : public BreakableObstacle
{
public:
	FenceObstacle(Module* moduleAt, Vector2 position);
	~FenceObstacle() {}

	update_status Update();
	bool Render();
	bool CleanUp();

private:
	Texture2D* fenceTexture = nullptr;
	Rectangle  fenceTextureRec = { 47, 0, 15, 16 };
};