#include "BreakableObstacle.h"

#include "MapObject.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

#include <raymath.h>

BreakableObstacle::BreakableObstacle(Module* moduleAt, Vector2 position, Vector2 size) : Obstacle(moduleAt, position)
{
	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	const Box2DFactory& factory = moduleAt->App->physics->factory();
	body = factory.CreateBox({ position.x,position.y }, size.x, size.y, fixtureData);
	body->SetType(PhysBody::BodyType::Static);

	sensor.SetFixtureToTrack(body, 0);

	uint16 categoryBits = moduleAt->App->physics->OBSTACLE_LAYER;
	uint16 maskBits = moduleAt->App->physics->VEHICLE_LAYER | moduleAt->App->physics->BOUNDARY_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);
}

update_status BreakableObstacle::Update()
{
	Obstacle::Update();

	return UPDATE_CONTINUE;
}

bool BreakableObstacle::CleanUp()
{
	Obstacle::CleanUp();
	return true;
}

void BreakableObstacle::OnHit()
{
	body->SetSensor(0,true);
}
