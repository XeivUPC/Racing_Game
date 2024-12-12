#include "ParticleSystem.h"
#include "Particle.h"

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
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particle == particles[i])
		{
			index = i;
			break;
		}
	}
	if (index == -1)
		return;
	particles.erase(particles.begin() + index);
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
