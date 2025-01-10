#pragma once

#include "Globals.h"
#include "ModuleScene.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>
#include <string>

class PhysBody;
class PhysJoint;
class Player;
class PauseMenu;
class GameMode;
class RaceTrack;
class ConeObstacle;
class RockObstacle;
class FenceObstacle;
class GamePositionsDisplayer;
class Pilot;
class GameDebug;

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
	void SetPlayerVehicle(string type, Color color);
	void SetVehicleType(string type, int amount);
	void SetPlayerCharacter(int character);
	int GetPilotAmount();

	vector<Pilot*> GetRacePlacePositions() const;
	int GetRacePlayerPosition() const;

public:
	PauseMenu* pauseMenu = nullptr;

	RaceTrack* track = nullptr;

	ConeObstacle* tree = nullptr;
	RockObstacle* rock = nullptr;
	FenceObstacle* fence = nullptr;

	GameMode* mode = nullptr;
	GamePositionsDisplayer* positionsDisplayer = nullptr;
	Player* player = nullptr;
	vector<Pilot*> pilots;
private:
	string trackPath = "";
	string player_vehicle_type="";
	Color player_vehicle_color=WHITE;
	int playerCharacter=0;
	string vehicle_type="";
	int vehicleTypeAmount=0;
	void SetPilotsCharacters();

	GameDebug* debugGame= nullptr;
};
