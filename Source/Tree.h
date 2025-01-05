#pragma once
#include "PushableObstacle.h"
#include "MapObject.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class Tree : public PushableObstacle
{
public:
	Tree(Module* moduleAt, Vector2 position);
	~Tree() {}

	update_status Update();
	bool Render();
	bool CleanUp();

private:
	Texture2D* treeTexture = nullptr;
	Rectangle  treeTextureRec = { 80, 0, 32, 32 };
};