#include "Tree.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

Tree::Tree(Module* moduleAt, Vector2 position) : MapObject(moduleAt)
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

update_status Tree::Update()
{
	if (sensor.OnTriggerEnter() && enabled) {
		OnTrigger();
	}

	Render();

    return UPDATE_CONTINUE;
}

bool Tree::Render()
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

bool Tree::CleanUp()
{
	delete body;
    return true;
}

void Tree::Enable()
{
	enabled = true;
}

void Tree::Disable()
{
	enabled = false;
}

void Tree::Activate()
{
	activated = true;
}

void Tree::Deactivate()
{
	activated = false;
}

Vector2 Tree::GetPos()
{
    return body->GetPosition();
}

double Tree::GetRotation()
{
    return body->GetAngle();
}

void Tree::OnTrigger()
{
	Activate();
}
