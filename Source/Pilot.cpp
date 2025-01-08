#include "Pilot.h"
#include "Vehicle.h"
#include "AnimationSystem.h"
#include "SceneGame.h"
#include "ModuleTexture.h"
#include "Application.h"
#include "ModulePhysics.h"


Pilot::Pilot(SceneGame* gameAt, RaceTrack* track, std::string vehicleType, Color vehicleColor) : MapObject((Module*)gameAt)
{
	this->gameAt = gameAt;
	this->track = track;

	vehicle = new Vehicle(moduleAt,this, vehicleType, vehicleColor);
	checkpoint = 0;
	lap = 0;

	explosionTex = gameAt->App->texture->GetTexture("explosion");

	/* Create Animations */

	//Button Exit
	explosionAnimator = new Animator(gameAt->App);

	AnimationData explodeAnim = AnimationData("explode");
	for (int i = 0; i < 13; i++) {
		explodeAnim.AddSprite(Sprite{ explosionTex,{(float)i, 0}, {64,64} });
	}

	explosionAnimator->AddAnimation(explodeAnim);
	explosionAnimator->AddAnimation(explodeAnim);
	explosionAnimator->AddAnimation(explodeAnim);
	explosionAnimator->SetSpeed(0.1f);
	explosionAnimator->SelectAnimation("explode", false);
}

Pilot::~Pilot()
{
}

bool Pilot::Start()
{
	return true;
}

update_status Pilot::Update()
{
	if (exploding) {
		explosionAnimator->Animate(vehicle->body->GetPhysicPosition(), {-32,-32}, vehicle->body->GetAngle(), 3, false);
		explosionAnimator->Update();
		if (explosionAnimator->HasAnimationFinished()) {
			exploding = false;
		}
	}
	return UPDATE_CONTINUE;
}

bool Pilot::Render()
{
	vehicle->Render();
	return true;
}

bool Pilot::CleanUp()
{
	vehicle->CleanUp();
	delete vehicle;
	if (explosionAnimator != nullptr) {
		delete explosionAnimator;
		explosionAnimator = nullptr;
	}
	return true;
}

void Pilot::AddLap()
{
	lap++;
	checkpoint = 0;
}

void Pilot::AddCheckpoint()
{
	checkpoint++;
}

int Pilot::CurrentCheckpoint()
{
	return checkpoint;
}

int Pilot::CurrentLap()
{
	return lap;
}

void Pilot::SetCharacterIndex(int index)
{
	characterIndex = index;
}

std::string Pilot::GetPilotName()
{
	return pilotName;
}

void Pilot::Explode()
{
	exploded = true;
	vehicle->Explode();
}

bool Pilot::IsExploded() const
{
	return exploded;
}

void Pilot::BeginExplosion()
{
	exploding = true;
	Explode();
}
