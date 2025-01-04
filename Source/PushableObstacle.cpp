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

}

bool PushableObstacle::CleanUp()
{
	delete body;
	return true;
}

void PushableObstacle::OnHit()
{
}

