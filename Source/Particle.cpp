#include "Particle.h"

Particle::Particle( Vector2 position, float lifeTime)
{
	this->lifeTime = lifeTime;
	this->position = position;
}

Particle::~Particle()
{
}

update_status Particle::Update()
{
	if (lifeTime < life_timer.ReadSec()) {
		CleanUp();
		delete this;
	}

	return UPDATE_CONTINUE;
}

bool Particle::CleanUp()
{
	system->RemoveParticle(this);
	return true;
}

float Particle::GetLifePercentage()
{
	return  (1 - life_timer.ReadSec() / lifeTime) * 100;
}

void Particle::Init(ParticleSystem* system)
{
	this->system = system;
}
