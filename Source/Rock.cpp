#include "Rock.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

Rock::Rock(Module* moduleAt, Vector2 position) : FixedObstacle(moduleAt, position, { PIXEL_TO_METERS(47) * 3, PIXEL_TO_METERS(63) * 3 })
{
	//Get Texture
	rockTexture = moduleAt->App->texture->GetTexture("objectsSpring");
}

update_status Rock::Update()
{
	FixedObstacle::Update();

	return UPDATE_CONTINUE;
}

bool Rock::Render()
{
	moduleAt->App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	moduleAt->App->renderer->Draw(*rockTexture, body->GetPhysicPosition(), {0,0}, &rockTextureRec);

	return true;
}

bool Rock::CleanUp()
{
	return false;
}
