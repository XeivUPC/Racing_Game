#include "ConeObstacle.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

ConeObstacle::ConeObstacle(Module* moduleAt, Vector2 position) : PushableObstacle(moduleAt, position, { PIXEL_TO_METERS(15) * 3, PIXEL_TO_METERS(15) * 3 }, 2,1)
{
	//Get Texture
	treeTexture = moduleAt->App->texture->GetTexture("cone");
}

update_status ConeObstacle::Update()
{
	PushableObstacle::Update();

	return UPDATE_CONTINUE;
}

bool ConeObstacle::Render()
{
	Vector2 treeRotatedOffset = {
	   -treeTextureRec.width / 2.f,
	   -treeTextureRec.height / 2.f
	};

	double radianAngle = body->GetAngle();

	moduleAt->App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_4);
	moduleAt->App->renderer->Draw(*treeTexture, body->GetPhysicPosition(), treeRotatedOffset, &treeTextureRec, RAD2DEG * radianAngle, 1.f * 3, (int)cos(-treeRotatedOffset.x), (int)sin(-treeRotatedOffset.y));

	return true;
}

bool ConeObstacle::CleanUp()
{
	PushableObstacle::CleanUp();
	return true;
}


