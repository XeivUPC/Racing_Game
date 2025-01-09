#pragma once
#include "MapObject.h"
#include <string>
#include <vector>
#include <raymath.h>

using namespace std;

class PhysBody;
class Obstacle;
class MapLapSensor;

class RaceTrack : public MapObject
{
public:

	RaceTrack(Module* moduleAt, string trackPath);
	~RaceTrack();
	vector<MapLapSensor*>GetTrackSensors();
	vector<Vector2>GetTrackStartingPositions();
	update_status Update();
	bool Render();
	bool CleanUp();
	float GetScale();

private:

	void LoadTrack();
	string ResolvePath(string basePath, string relativePath);

	void FromStringToVertices(std::string stringData, float scale, std::vector<Vector2>& vector);

	string trackPath = "";
	float mapScale = 1;

	Texture* trackTexture = nullptr;
	vector<PhysBody*> trackColliders;
	vector<Obstacle*> trackObstacles;
	vector<Vector2> startingPositions;
	vector<MapLapSensor*> mapLapSensors;
};