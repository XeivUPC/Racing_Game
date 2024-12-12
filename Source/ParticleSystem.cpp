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
	for (const auto& particle : particles)
		particle->Update();
}
