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
	body = factory.CreateBox(position, PIXEL_TO_METERS(treeTextureRec.width / 2), PIXEL_TO_METERS(treeTextureRec.height), fixtureData);
	body->SetType(PhysBody::BodyType::Dynamic);
	body->SetFriction(body->GetFixtureCount(), 5000);
	sensor.SetFixtureToTrack(body, 0);

	sensor.AcceptOnlyTriggers(false);

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
	UpdateFriction();

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
	moduleAt->App->renderer->Draw(*treeTexture, body->GetPhysicPosition(), treeRotatedOffset, &treeTextureRec, RAD2DEG * radianAngle, 1.f, (int)cos(-treeRotatedOffset.x), (int)sin(-treeRotatedOffset.y));

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

void Tree::UpdateFriction()
{
	// Set linear damping (slows down the object's movement over time)
	body->SetLinearDamping(0.5f);  // Adjust the damping value to your needs

	// Set angular damping (if needed for rotation)
	body->SetAngularDamping(0.5f);  // Adjust for rotational damping

}

Vector2 Tree::GetLateralVelocity()
{
	Vector2 currentRightNormal = body->GetWorldVector({ 1,0 });
	return Vector2Scale(currentRightNormal, Vector2DotProduct(currentRightNormal, body->GetLinearVelocity()));
}

Vector2 Tree::GetForwardVelocity()
{
	Vector2 currentForwardNormal = body->GetWorldVector({ 0, 1 });
	return Vector2Scale(currentForwardNormal, Vector2DotProduct(currentForwardNormal, body->GetLinearVelocity()));
}
void Tree::OnTrigger()
{
	Activate();
}
