#pragma once
#include <vector>
#include "Module.h"

class Particle;

class ParticleSystem
{
public:
	ParticleSystem(Module* moduleAt);
	~ParticleSystem();

	void AddParticle(Particle* particle);
	void RemoveParticle(Particle* particle);
	void UpdateParticles();
private:
	std::vector<Particle*> particles;
	Module* moduleAt;
};

