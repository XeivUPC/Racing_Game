#pragma once
#include "Module.h"
#include "ParticleSystem.h"
#include "Timer.h"

class Particle
{
	friend ParticleSystem;
public:

	Particle(Vector2 position, float lifeTime);
	virtual ~Particle();
	virtual bool Update();

	float GetLifePercentage();
private:
	float lifeTime = 1;
	Timer life_timer;
protected:

	virtual bool CleanUp();
	virtual void Init(ParticleSystem* system);

	ParticleSystem* system=nullptr;
	Module* moduleAt=nullptr;

	Vector2 position = {0,0};
	Texture2D* texture = nullptr;


};