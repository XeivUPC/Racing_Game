#include "DriftParticle.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

DriftParticle::DriftParticle(Vector2 position, double angle, float lifeTime) : Particle(position, lifeTime)
{
	this->angle = angle;
}

DriftParticle::~DriftParticle()
{

}

bool DriftParticle::Update()
{
	if (texture == nullptr || system == nullptr) {
		CleanUp();
		return true;
	}
	/// RenderParticle
	Rectangle rect = { 0,0,(float)texture->width ,(float)texture->height };
	Vector2 offset = {-texture->width/2.f ,-texture->height/2.f };

	unsigned int alpha = (unsigned int)(255 * GetLifePercentage()/100) +1;
	if (alpha < 0)
		alpha = 0;
	// Create the color with white RGB values and calculated alpha
	Color color = { 255, 255, 255, (unsigned char)alpha };

	moduleAt->App->renderer->Draw(*texture, position, offset,&rect,RAD2DEG * angle, 3,0,0, color);
	Particle::Update();
	return true;
}

bool DriftParticle::CleanUp()
{
	Particle::CleanUp();
	return false;
}

void DriftParticle::Init(ParticleSystem* system)
{
	Particle::Init(system);
	texture = moduleAt->App->texture->GetTexture("DriftMark");
}
