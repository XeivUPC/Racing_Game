#pragma once
#include "Vehicle.h"
#include "Module.h"
#include "AnimationSystem.h"
#include "ParticleSystem.h"

class PhysJoint;

class Car : public Vehicle
{
public:
	Car(Module* moduleAt);
	~Car();
	update_status Update();
	bool CleanUp();
private:
	float maxForwardSpeed = 150;
	float maxBackwardSpeed = -70;
	float backTireMaxDriveForce = 50;
	float frontTireMaxDriveForce = 150;
	float backTireMaxLateralImpulse = 12.5f;
	float frontTireMaxLateralImpulse = 8.5f;

	Texture2D* carTexture;
	Rectangle carTextureRec;
	Texture2D* wheelTexture;
	Rectangle wheelTextureRec;

	Animator* animatorWheel;
	ParticleSystem* particleSystem;

protected:

};
