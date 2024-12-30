#pragma once
#include "MapObject.h"
#include <string>
#include <vector>

using namespace std;

class PhysBody;

class RackTrack : public MapObject
{
public:

	RackTrack(Module* moduleAt, string trackPath);
	~RackTrack();

	update_status Update();
	bool Render();
	bool CleanUp();

private:

	void LoadTrack();
	string trackPath;

	Texture* trackTexture = nullptr;
	vector<PhysBody*> trackColliders;
};