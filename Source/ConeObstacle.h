#pragma once
#include "PushableObstacle.h"
#include "MapObject.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class ConeObstacle : public PushableObstacle
{
public:
	ConeObstacle(Module* moduleAt, Vector2 position);
	~ConeObstacle() {}

	update_status Update();
	bool Render();
	bool CleanUp();

private:
	Texture2D* treeTexture = nullptr;
	Rectangle  treeTextureRec = { 0, 0, 15, 15 };
};