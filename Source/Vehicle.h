#pragma once
#include "MapObject.h"
#include <vector>
#include <string>
#include <pugixml.hpp>

using namespace pugi;
using namespace std;

class Wheel;
class PhysBody;
class ParticleSystem;

class Vehicle : public MapObject
{
public:

	Vehicle(Module* gameAt, string id);
	~Vehicle();
	update_status Update();
	bool CleanUp();
	double GetRotation();

private:
	void GetInput();

	void CreateVehicle(string id);
	Wheel* CreateWheel(xml_node wheel_node);

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

