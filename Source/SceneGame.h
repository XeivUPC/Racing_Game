#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class Vehicle;

class SceneGame : public ModuleScene
{
public:
	SceneGame(Application* app, bool start_enabled = true);
	~SceneGame();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

public:
	Vehicle* car;
};
