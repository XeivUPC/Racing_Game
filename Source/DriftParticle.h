#pragma once
#include "Particle.h"

class DriftParticle : public Particle
{
public:
	DriftParticle(Vector2 position, double angle, float lifeTime);
	~DriftParticle();
	update_status Update();
	bool CleanUp();

private:
	void Init(ParticleSystem* system);
	double angle;
};