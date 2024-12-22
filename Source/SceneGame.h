#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class Vehicle;
class UISlider;

class SceneGame : public ModuleScene
{
public:
	SceneGame(Application* app, bool start_enabled = true);
	~SceneGame();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Vehicle* car;
	Font font;
};
