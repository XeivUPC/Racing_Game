#include "Tree.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

#include <raymath.h>

Tree::Tree(Module* moduleAt, Vector2 position) : PushableObstacle(moduleAt, position, { PIXEL_TO_METERS(32) * 3, PIXEL_TO_METERS(32) * 3 }, 2,1)
{
	//Get Texture
	treeTexture = moduleAt->App->texture->GetTexture("objectsSpring");
}

update_status Tree::Update()
{
	PushableObstacle::Update();

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
	PushableObstacle::CleanUp();
	return true;
}


