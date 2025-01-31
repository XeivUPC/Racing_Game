#pragma once
#include <string>
#include "MapObject.h"

class SceneGame;
class Vehicle;
struct Vector2;
class RaceTrack;
class Animator;

class Pilot : public MapObject
{
protected:
	int lap=0;
	int checkpoint=0;
	RaceTrack* track = nullptr;
	SceneGame* gameAt = nullptr;
	std::string pilotName = "The Unnamed";
	bool exploded = false;
	bool exploding = false;
	Texture2D* explosionTex = nullptr;
	Animator* explosionAnimator = nullptr;
public:
	Pilot(SceneGame* gameAt, RaceTrack* track, std::string vehicleType, Color vehicleColor);
	~Pilot();
	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

	void AddLap();
	void AddCheckpoint();
	int CurrentCheckpoint();
	int CurrentLap();
	void SetCharacterIndex(int index);
	std::string GetPilotName();
	void SetPilotName(std::string name);
	void Explode();
	bool IsExploded() const;
	void BeginExplosion();
	Vehicle* vehicle = nullptr;
	int characterIndex = 0;
};