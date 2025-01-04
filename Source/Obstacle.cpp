#include "Obstacle.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

Obstacle::Obstacle(Module* moduleAt, Vector2 position) : MapObject(moduleAt)
{
	//Create body
	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);
	
	const Box2DFactory& factory = moduleAt->App->physics->factory();
	body = factory.CreateBox(position, PIXEL_TO_METERS(treeTextureRec.width / 2)*3, PIXEL_TO_METERS(treeTextureRec.height / 3)*3, fixtureData);
	body->SetType(PhysBody::BodyType::Dynamic);
	sensor.SetFixtureToTrack(body, 0);

	sensor.AcceptOnlyTriggers(false);

	body->SetLinearDamping(linearDamping);
	body->SetAngularDamping(angularDamping);

	uint16 categoryBits = moduleAt->App->physics->OBSTACLE_LAYER;
	uint16 maskBits = moduleAt->App->physics->VEHICLE_LAYER | moduleAt->App->physics->BOUNDARY_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);

	Enable();

	//Get Texture
	treeTexture = moduleAt->App->texture->GetTexture("objectsSpring");

	/*if (map == Winter)
	{
		treeTexture = App->texture->GetTexture("objectsWinter");
	}
	else
	{
		treeTexture = App->texture->GetTexture("objectsSpring");
	}*/
	
}

update_status Obstacle::Update()
{
	if (sensor.OnTriggerEnter() && enabled) {
		OnTrigger();
	}

	Render();

    return UPDATE_CONTINUE;
}

bool Obstacle::Render()
{
	Vector2 treeRotatedOffset = {
	   -treeTextureRec.width / 2.f,
	   -treeTextureRec.height / 2.f
	};

	double radianAngle = body->GetAngle();

	moduleAt->App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	moduleAt->App->renderer->Draw(*treeTexture, body->GetPhysicPosition(), treeRotatedOffset, &treeTextureRec, RAD2DEG * radianAngle, 1.f * 3, (int)cos(-treeRotatedOffset.x), (int)sin(-treeRotatedOffset.y));

    return true;
}

bool Obstacle::CleanUp()
{
	delete body;
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
