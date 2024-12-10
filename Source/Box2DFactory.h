#pragma once
#include "ModulePhysics.h"
#include <vector>


class PhysBody;
class PhysJoint;

class Box2DFactory //factory Box2DFactory --> PhysicsFactory
{
public:
	Box2DFactory(b2World* world);
	~Box2DFactory();
	
	PhysBody* CreateCircle(Vector2 position,float radius, b2FixtureUserData userData = b2FixtureUserData()) const;
	PhysBody* CreateBox(Vector2 position, float width, float height, b2FixtureUserData userData = b2FixtureUserData())const;
	PhysBody* CreateBevelBox(Vector2 position, float width, float height, float bevelSize, b2FixtureUserData userData = b2FixtureUserData())const;
	PhysBody* CreateCapsule(Vector2 position, float width, float height, float radius, b2FixtureUserData userData = b2FixtureUserData())const;
	PhysBody* CreateChain(Vector2 position, const std::vector<Vector2> vertices, b2FixtureUserData userData = b2FixtureUserData()) const;

	int AddCircle(PhysBody* bodyToAddTo, Vector2 offset, float radius, b2FixtureUserData userData = b2FixtureUserData())const;
	int AddBox(PhysBody* bodyToAddTo, Vector2 offset, float width, float height, b2FixtureUserData userData = b2FixtureUserData())const;



	PhysJoint* CreateRevoluteJoint(PhysBody* bodyA, PhysBody* bodyB, const Vector2& localAnchorA, const Vector2& localAnchorB,
		bool enableLimit = false, float lowerAngle = 0.0f, float upperAngle = 0.0f,
		bool enableMotor = false, float motorSpeed = 0.0f, float maxMotorTorque = 0.0f)const;

	PhysJoint* CreatePrismaticJoint(PhysBody* bodyA, PhysBody* bodyB, const Vector2& anchor, const Vector2& axis,
		bool enableLimit = false, float lowerTranslation = 0.0f, float upperTranslation = 0.0f,
		bool enableMotor = false, float motorSpeed = 0.0f, float maxMotorForce = 0.0f)const;

	PhysJoint* CreateDistanceJoint(PhysBody* bodyA, PhysBody* bodyB, const Vector2& anchorA, const Vector2& anchorB,
		float length, float frequencyHz = 0.0f, float dampingRatio = 0.0f)const;

	PhysJoint* CreatePulleyJoint(PhysBody* bodyA, PhysBody* bodyB,
		const Vector2& groundAnchorA, const Vector2& groundAnchorB,
		const Vector2& anchorA, const Vector2& anchorB,
		float ratio, float lengthA = 0.0f, float lengthB = 0.0f)const;

	PhysJoint* CreateGearJoint(PhysJoint* joint1, PhysJoint* joint2, float ratio)const;

	PhysJoint* CreateWeldJoint(PhysBody* bodyA, PhysBody* bodyB, const Vector2& anchor, float frequencyHz = 0.0f, float dampingRatio = 0.0f)const;

	PhysJoint* CreateMouseJoint(PhysBody* bodyA, PhysBody* staticBodyAnchor, const Vector2& target, float maxForce, float frequencyHz, float dampingRatio)const;


private:
	b2CircleShape CreateCircleShape(float radius, b2Vec2 offset = {0,0})const;
	b2PolygonShape CreateBoxShape(float width, float height, b2Vec2 offset = { 0,0 })const;

	b2World* world = nullptr;
};

