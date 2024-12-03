#pragma once

#include "ModulePhysics.h"

class PhysBody;

class Box2DFactory //factory Box2DFactory --> PhysicsFactory
{
public:
	Box2DFactory(b2World* world);
	~Box2DFactory();
	
	PhysBody* CreateCircle(b2Vec2 position,float radius, b2FixtureUserData userData = b2FixtureUserData());
	PhysBody* CreateBox(b2Vec2 position, float width, float height, b2FixtureUserData userData = b2FixtureUserData());
	PhysBody* CreateBevelBox(b2Vec2 position, float width, float height, float bevelSize, b2FixtureUserData userData = b2FixtureUserData());
	PhysBody* CreateCapsule(b2Vec2 position, float width, float height, float radius, b2FixtureUserData userData = b2FixtureUserData());

	int AddCircle(PhysBody* bodyToAddTo, b2Vec2 offset, float radius, b2FixtureUserData userData = b2FixtureUserData());
	int AddBox(PhysBody* bodyToAddTo, b2Vec2 offset, float width, float height, b2FixtureUserData userData = b2FixtureUserData());

private:
	b2CircleShape CreateCircleShape(float radius, b2Vec2 offset = b2Vec2_zero);
	b2PolygonShape CreateBoxShape(float width, float height, b2Vec2 offset = b2Vec2_zero);

	b2World* world = nullptr;
};

