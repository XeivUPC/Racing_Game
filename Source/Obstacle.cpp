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

}

update_status Obstacle::Update()
{
	if (sensor.OnTriggerEnter()) {
		OnTrigger();
	}

    return UPDATE_CONTINUE;
}

bool Obstacle::CleanUp()
{
	delete body;
    return true;
}

Vector2 Obstacle::GetPos()
{
    return body->GetPosition();
}

double Obstacle::GetRotation()
{
    return body->GetAngle();
}

void Obstacle::OnHit()
{
}

void Obstacle::OnTrigger()
{
	OnHit();
}
