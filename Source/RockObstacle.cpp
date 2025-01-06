#include "RockObstacle.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

RockObstacle::RockObstacle(Module* moduleAt, Vector2 position) : FixedObstacle(moduleAt, position, { PIXEL_TO_METERS(15) * 3, PIXEL_TO_METERS(16) * 3 })
{
	//Get Texture
	rockTexture = moduleAt->App->texture->GetTexture("objectsSpring");
}

update_status RockObstacle::Update()
{
	FixedObstacle::Update();

	return UPDATE_CONTINUE;
}

bool RockObstacle::Render()
{
	moduleAt->App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
	moduleAt->App->renderer->Draw(*rockTexture, body->GetPhysicPosition(), { -rockTextureRec.width / 2.f, -rockTextureRec.height / 2.f }, &rockTextureRec, 0, 1.f * 3);

	return true;
}

bool RockObstacle::CleanUp()
{
	FixedObstacle::CleanUp();
	return true;
}
