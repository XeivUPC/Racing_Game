#pragma once
#include "MapObject.h"
#include <vector>

using namespace std;

class Wheel;
class PhysBody;

class Vehicle : public MapObject
{
public:

	Vehicle(Module* gameAt);
	~Vehicle();
	update_status Update();
	bool CleanUp();

private:
	void GetInput();

protected:
	vector<Wheel*> wheels;
	PhysBody* body = nullptr;
	Vector2 moveInput;

};

