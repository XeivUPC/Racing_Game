#pragma once
#include "Particle.h"

class DriftParticle : public Particle
{
public:
	DriftParticle(Vector2 position, double angle, float lifeTime);
	~DriftParticle();
	bool Update();

private:
	bool CleanUp();
	void Init(ParticleSystem* system);
	double angle;
};