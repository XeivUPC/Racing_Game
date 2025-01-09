#pragma once
#include "MapObject.h"
#include "Timer.h"
#include <vector>
#include <string>

using namespace std;

class Wheel;
class PhysBody;
class ParticleSystem;
class Pilot;

class Vehicle : public MapObject
{
public:

	Vehicle(Module* moduleAt, Pilot* pilot, string id, Color vehicleColor);
	~Vehicle();
	update_status Update();
	bool Render();
	bool CleanUp();
	void SetInput(Vector2 input);
	void Explode();

	PhysBody* body = nullptr;
private:

	void CreateVehicle(string id);

	vector<Wheel*> steeringWheels;
	vector<Wheel*> throttlingWheels;
	vector<Wheel*> wheels;

	Vector2 moveInput = {0,0};
	Pilot* pilot = nullptr;

	float maxForwardSpeed = 150;
	float maxBackwardSpeed = -70;

	Texture2D* vehicleTexture = nullptr;
	Rectangle  vehicleTextureRecColor;
	Rectangle  vehicleTextureRecFixed;
	Color vehicleColor = WHITE;

	ParticleSystem* particleSystem = nullptr;

	string vehicleName="";
	string vehicleTitle="";
	string vehicleCreator="";
	string vehicleDescription="";

	Timer engineTimer;

	bool exploded = false;
};

