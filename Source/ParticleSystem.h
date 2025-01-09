#pragma once
#include <vector>
#include "Module.h"

class Particle;

class ParticleSystem
{
	friend Particle;
public:
	ParticleSystem(Module* moduleAt);
	~ParticleSystem();

	void AddParticle(Particle* particle);
	void UpdateParticles();
private:
	void AddParticleToRemove(Particle* particle);
	void RemoveParticle(Particle* particle);
	std::vector<Particle*> particles;
	std::vector<Particle*> particlesToRemove;
	Module* moduleAt = nullptr;
};

