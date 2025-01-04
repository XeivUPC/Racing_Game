#include "PushableObstacle.h"

#include "MapObject.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

PushableObstacle::PushableObstacle(Module* moduleAt, Vector2 position) : Obstacle(moduleAt, position)
{
	//Create body
	body->SetLinearDamping(linearDamping);
	body->SetAngularDamping(angularDamping);

	uint16 categoryBits = moduleAt->App->physics->OBSTACLE_LAYER;
	uint16 maskBits = moduleAt->App->physics->VEHICLE_LAYER | moduleAt->App->physics->BOUNDARY_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);

	Enable();
}

update_status PushableObstacle::Update()
{
	if (sensor.OnTriggerEnter() && enabled) {
		OnTrigger();
	}

	return UPDATE_CONTINUE;
}

bool PushableObstacle::CleanUp()
{
	delete body;
	return true;
}

void PushableObstacle::Enable()
{
	enabled = true;
}

void PushableObstacle::Disable()
{
	enabled = false;
}

void PushableObstacle::Activate()
{
	activated = true;
}

void PushableObstacle::Deactivate()
{
	activated = false;
}

Vector2 PushableObstacle::GetPos()
{
	return body->GetPosition();
}

double PushableObstacle::GetRotation()
{
	return body->GetAngle();
}

void PushableObstacle::OnTrigger()
{
	Activate();
}
