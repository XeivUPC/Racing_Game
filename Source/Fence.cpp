#include "Fence.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

Fence::Fence(Module* moduleAt, Vector2 position) : BreakableObstacle(moduleAt, position, { PIXEL_TO_METERS(47) * 3, PIXEL_TO_METERS(63) * 3 })
{
	//Get Texture
	fenceTexture = moduleAt->App->texture->GetTexture("objectsSpring");
}

update_status Fence::Update()
{
    BreakableObstacle::Update();

    return UPDATE_CONTINUE;
}

bool Fence::Render()
{
    moduleAt->App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_5);
    moduleAt->App->renderer->Draw(*fenceTexture, body->GetPhysicPosition(), { 0,0 }, &fenceTextureRec);

    return true;
}

bool Fence::CleanUp()
{
    BreakableObstacle::CleanUp();
    return true;
}