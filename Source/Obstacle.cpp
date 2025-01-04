#include "Obstacle.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

Obstacle::Obstacle(Module* moduleAt, Vector2 position) : MapObject(moduleAt)
{
	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	
	sensor.AcceptOnlyTriggers(false);

	/*uint16 categoryBits = moduleAt->App->physics->OBSTACLE_LAYER;
	uint16 maskBits = moduleAt->App->physics->VEHICLE_LAYER | moduleAt->App->physics->BOUNDARY_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);*/

	Enable();
}

update_status Obstacle::Update()
{
	if (sensor.OnTriggerEnter() && enabled) {
		OnTrigger();
	}

    return UPDATE_CONTINUE;
}

bool Obstacle::CleanUp()
{
    return true;
}

void Obstacle::Enable()
{
	enabled = true;
}

void Obstacle::Disable()
{
	enabled = false;
}

void Obstacle::Activate()
{
	activated = true;
}

void Obstacle::Deactivate()
{
	activated = false;
}

Vector2 Obstacle::GetPos()
{
    return body->GetPosition();
}

double Obstacle::GetRotation()
{
    return body->GetAngle();
}

void Obstacle::OnTrigger()
{
	Activate();
}
