#pragma once
#include "MapObject.h"
#include <string>
#include <vector>
#include <raymath.h>

using namespace std;

class PhysBody;
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

private:

	void LoadTrack();
	string ResolvePath(string basePath, string relativePath);

	void FromStringToVertices(std::string stringData, std::vector<Vector2>& vector);

	string trackPath;

	Texture* trackTexture = nullptr;
	vector<PhysBody*> trackColliders;
	vector<Vector2> startingPositions;
	vector<MapLapSensor*> mapLapSensors;
};