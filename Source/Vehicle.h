#pragma once
#include "MapObject.h"
#include <vector>
#include <string>

using namespace std;

class Wheel;
class PhysBody;
class ParticleSystem;

class Vehicle : public MapObject
{
public:

	Vehicle(Module* moduleAt, string id);
	~Vehicle();
	update_status Update();
	bool Render();
	bool CleanUp();
	double GetRotation();
	void SetInput(Vector2 input);
	Vector2 GetPos();

private:

	void CreateVehicle(string id);

	vector<Wheel*> steeringWheels;
	vector<Wheel*> throttlingWheels;
	vector<Wheel*> wheels;

	PhysBody* body = nullptr;
	Vector2 moveInput;

	float maxForwardSpeed = 150;
	float maxBackwardSpeed = -70;

	Texture2D* vehicleTexture;
	Rectangle  vehicleTextureRec;


	ParticleSystem* particleSystem;

	string vehicleName;
	string vehicleTitle;
	string vehicleCreator;
	string vehicleDescription;
};

