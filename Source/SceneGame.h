#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class Player;
class PauseMenu;
class RaceTrack;
class RaceMode;

class SceneGame : public ModuleScene
{
public:
	SceneGame(Application* app, bool start_enabled = false);
	~SceneGame();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

public:
	Player* player;
	PauseMenu* pauseMenu;
	RaceTrack* track;
	RaceMode* mode;
};
