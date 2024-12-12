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
	void AddParticleToRemove(Particle* particle);
	void UpdateParticles();
private:
	void RemoveParticle(Particle* particle);
	std::vector<Particle*> particles;
	std::vector<Particle*> particlesToRemove;
	Module* moduleAt;
};

