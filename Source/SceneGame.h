#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>
#include <string>

class PhysBody;
class Player;
class PauseMenu;
class GameMode;
class RaceTrack;
class Tree;
class Pilot;

using namespace std;

class SceneGame : public ModuleScene
{
public:
	SceneGame(Application* app, bool start_enabled = false);
	~SceneGame();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

	void SetUpTrack(string path);
	void SetMode(GameMode* mode);

	vector<Pilot*> GetRacePlacePositions() const;

public:
	PauseMenu* pauseMenu;

	RaceTrack* track;

	Tree* tree;
	GameMode* mode;

	Player* player;
	vector<Pilot*> pilots;
private:
	string trackPath = "";
};
