#include "PushableObstacle.h"

#include "MapObject.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

PushableObstacle::PushableObstacle(Module* moduleAt, Vector2 position, Vector2 size,float linearDamping, float angularDamping) : Obstacle(moduleAt, position)
{
	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	const Box2DFactory& factory = moduleAt->App->physics->factory();
	body = factory.CreateBox({ position.x,position.y }, size.x, size.y, fixtureData);

	this->linearDamping = linearDamping;
	this->angularDamping = angularDamping;
	body->SetLinearDamping(linearDamping);
	body->SetAngularDamping(angularDamping);

	sensor.SetFixtureToTrack(body, 0);

	uint16 categoryBits = moduleAt->App->physics->OBSTACLE_LAYER;
	uint16 maskBits = moduleAt->App->physics->VEHICLE_LAYER | moduleAt->App->physics->BOUNDARY_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);

}

update_status PushableObstacle::Update()
{
	Obstacle::Update();

	return UPDATE_CONTINUE;
}

bool PushableObstacle::CleanUp()
{
	Obstacle::CleanUp();
	return true;
}

void PushableObstacle::OnHit()
{
}

