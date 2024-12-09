#pragma once

#include "Module.h"
#include "Globals.h"

#include "box2d/box2d.h"


#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 1/PIXELS_PER_METER // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody();
	~PhysBody();

	Vector2 GetPhysicPosition() const;

	void SetPosition(float x, float y);
	void ApplyForce(const Vector2& force, const Vector2& point);
	void ApplyLinearImpulse(const Vector2& impulse, const Vector2& point);
	void SetVelocity(const Vector2& velocity);
	Vector2 GetVelocity() const;
	float GetAngle() const;

	void SetFriction(size_t fixtureIndex, float friction);
	void SetDensity(size_t fixtureIndex, float density);
	void SetRestitution(size_t fixtureIndex, float restitution);
	void SetRestitutionThreshold(size_t fixtureIndex, float restitutionThreshold);
	void SetSensor(size_t fixtureIndex, bool isSensor);
	void SetFilter(size_t fixtureIndex, uint16 categoryBits, uint16 maskBits, int16 groupIndex);

	float GetFriction(size_t fixtureIndex) const;
	float GetDensity(size_t fixtureIndex) const;
	float GetRestitution(size_t fixtureIndex) const;
	float GetRestitutionThreshold(size_t fixtureIndex) const;
	bool IsSensor(size_t fixtureIndex) const;
	b2Filter GetFilter(size_t fixtureIndex) const;

	size_t GetFixtureCount() const;

	void DestroyBody();

private:
	b2Fixture* GetFixtureByIndex(size_t fixtureIndex) const;

public:
	int width, height = 0;
	b2Body* body = nullptr;
};


class Box2DFactory;
class CollisionsDispatcher;

// Module --------------------------------------
class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	const Box2DFactory& factory();

private:
	bool debug = false;
	b2World* world = nullptr;

	CollisionsDispatcher* collisionsManager = nullptr;
	Box2DFactory* box2Dfactory = nullptr;
};