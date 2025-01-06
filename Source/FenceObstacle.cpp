#include "FenceObstacle.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

FenceObstacle::FenceObstacle(Module* moduleAt, Vector2 position) : BreakableObstacle(moduleAt, position, { PIXEL_TO_METERS(15) * 3, PIXEL_TO_METERS(16) * 3 })
{
	//Get Texture
	fenceTexture = moduleAt->App->texture->GetTexture("objectsSpring");
}

update_status FenceObstacle::Update()
{
    BreakableObstacle::Update();

    return UPDATE_CONTINUE;
}

bool FenceObstacle::Render()
{
    moduleAt->App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
    moduleAt->App->renderer->Draw(*fenceTexture, body->GetPhysicPosition(), { -fenceTextureRec.width / 2.f, -fenceTextureRec.height / 2.f }, &fenceTextureRec, 0, 1.f * 3);

    return true;
}

bool FenceObstacle::CleanUp()
{
    BreakableObstacle::CleanUp();
    return true;
}