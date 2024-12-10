#pragma once
#include "MapObject.h"
#include <vector>

using namespace std;

class Wheel;
class PhysBody;

class Vehicle : public MapObject
{
public:

	Vehicle(ModuleGame* gameAt);
	~Vehicle();
	update_status Update();
	bool CleanUp();

private:

protected:
	vector<Wheel*> wheels;
	PhysBody* body = nullptr;

};

