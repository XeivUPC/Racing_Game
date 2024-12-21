#include "Particle.h"

Particle::Particle( Vector2 position, float lifeTime)
{
	this->lifeTime = lifeTime;
	this->position = position;
}

Particle::~Particle()
{
}

bool Particle::Update()
{
	if (system == nullptr)
		return true;
	if (lifeTime < life_timer.ReadSec()) {
		system->AddParticleToRemove(this);
	}

	return true;
}

bool Particle::CleanUp()
{
	return true;
}

float Particle::GetLifePercentage()
{
	return  (float)((1 - life_timer.ReadSec() / lifeTime) * 100);
}

void Particle::Init(ParticleSystem* system)
{
	this->system = system;
}
