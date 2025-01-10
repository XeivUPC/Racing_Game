#include "ParticleSystem.h"
#include "Particle.h"
#include <algorithm>

ParticleSystem::ParticleSystem(Module* moduleAt)
{
	this->moduleAt = moduleAt;
}

ParticleSystem::~ParticleSystem()
{
	for (size_t i = 0; particles.size() > 0;) {
		Particle* particle = particles[i];
		particle->CleanUp();
		RemoveParticle(particle);
		delete particle;
	}
}

void ParticleSystem::AddParticle(Particle* particle)
{
	if (particle->moduleAt != nullptr)
		return;
	particle->moduleAt = moduleAt;
	particles.emplace_back(particle);
	particle->Init(this);
}

void ParticleSystem::AddParticleToRemove(Particle* particle)
{
	particlesToRemove.emplace_back(particle);
}

void ParticleSystem::RemoveParticle(Particle* particle)
{
	int index = -1;

	auto it = std::find(particles.begin(), particles.end(), particle);
	if (it != particles.end()) {
		index  = std::distance(particles.begin(), it);
		particles.erase(particles.begin() + index);
	}
}

void ParticleSystem::UpdateParticles()
{
	particlesToRemove.clear();

	for (const auto& particle : particles) {
		if(particle != nullptr)
			particle->Update();
	}

	for (size_t i = 0; i < particlesToRemove.size(); i++) {
		Particle* particle = particlesToRemove[i];
		particle->CleanUp();
		RemoveParticle(particle);
		delete particle;
	}
}
