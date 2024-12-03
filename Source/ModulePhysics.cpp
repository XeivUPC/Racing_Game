#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "CollisionsManager.h"
#include "Box2DFactory.h"

#include "p2Point.h"

#include <math.h>



ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
	collisionsManager = new CollisionsManager();
	
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	
	b2Vec2 gravity = { 0,0 };
	world = new b2World(gravity);
	factory = new Box2DFactory(world);

	world->SetContactListener(collisionsManager);

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	float dt = GetFrameTime();
	world->Step(1/60.f, 6, 2);
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	

	if (IsKeyPressed(KEY_F1))
	{
		debug = !debug;
	}

	if (!debug)
	{
		return UPDATE_CONTINUE;
	}

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					
					DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), (float)METERS_TO_PIXELS(shape->m_radius), Color{0, 0, 0, 128});
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->m_count;
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->m_vertices[i]);
						if(i > 0)
							DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), RED);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->m_vertices[0]);
					DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), RED);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), GREEN);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), GREEN);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), BLUE);
				}
				break;
			}

			
		}
	}

	
	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	delete collisionsManager;
	delete factory;

	// Delete the whole physics world!
	delete world;

	return true;
}

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////

#pragma region PhysBody

PhysBody::PhysBody()
{
}

PhysBody::~PhysBody()
{
	DestroyBody();
}

Vector2 PhysBody::GetPhysicPosition() const
{
	b2Vec2 pos = body->GetPosition();
	int x = METERS_TO_PIXELS(pos.x);
	int y = METERS_TO_PIXELS(pos.y);
	return { (float)x,(float)y };
}

void PhysBody::SetPosition(float x, float y) {
	if (body) {
		body->SetTransform({ x, y }, body->GetAngle());
	}
}

void PhysBody::ApplyForce(const Vector2& force, const Vector2& point) {
	if (body) {
		body->ApplyForce({ force.x, force.y }, { point.x, point.y }, true);
	}
}

void PhysBody::ApplyLinearImpulse(const Vector2& impulse, const Vector2& point) {
	if (body) {
		
		body->ApplyLinearImpulse({ impulse.x, impulse.y }, {point.x, point.y}, true);
	}
}

void PhysBody::SetVelocity(const Vector2& velocity) {
	if (body) {
		body->SetLinearVelocity({ velocity.x,velocity.y});
	}
}

Vector2 PhysBody::GetVelocity() const {
	if (body) {
		b2Vec2 vel = body->GetLinearVelocity();
		return {vel.x,vel.y};
	}
	return {0,0};
}

float PhysBody::GetAngle() const {
	if (body) {
		return body->GetAngle();
	}
	return 0.0f;
}

b2Fixture* PhysBody::GetFixtureByIndex(size_t fixtureIndex) const {
	if (!body) return nullptr;
	b2Fixture* fixture = body->GetFixtureList();
	size_t i = 0;
	while (fixture && i < fixtureIndex) {
		fixture = fixture->GetNext();
		i++;
	}
	return fixture;
}

void PhysBody::SetFriction(size_t fixtureIndex, float friction) {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		fixture->SetFriction(friction);
	}
}

void PhysBody::SetDensity(size_t fixtureIndex, float density) {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		fixture->SetDensity(density);
		body->ResetMassData(); // Recalcular masa
	}
}

void PhysBody::SetRestitution(size_t fixtureIndex, float restitution) {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		fixture->SetRestitution(restitution);
	}
}

void PhysBody::SetRestitutionThreshold(size_t fixtureIndex, float restitutionThreshold)
{
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		fixture->SetRestitutionThreshold(restitutionThreshold);
	}
}

void PhysBody::SetSensor(size_t fixtureIndex, bool isSensor) {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		fixture->SetSensor(isSensor);
	}
}

b2Filter PhysBody::GetFilter(size_t fixtureIndex) const {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		return fixture->GetFilterData();
	}
	return {};
}

float PhysBody::GetFriction(size_t fixtureIndex) const {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		return fixture->GetFriction();
	}
	return 0.0f;
}

float PhysBody::GetDensity(size_t fixtureIndex) const {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		return fixture->GetDensity();
	}
	return 0.0f;
}

float PhysBody::GetRestitution(size_t fixtureIndex) const {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		return fixture->GetRestitution();
	}
	return 0.0f;
}

float PhysBody::GetRestitutionThreshold(size_t fixtureIndex) const
{
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		return fixture->GetRestitutionThreshold();
	}
	return 0.0f;
}

bool PhysBody::IsSensor(size_t fixtureIndex) const {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		return fixture->IsSensor();
	}
	return false;
}

void PhysBody::SetFilter(size_t fixtureIndex, uint16 categoryBits, uint16 maskBits, int16 groupIndex) {
	if (b2Fixture* fixture = GetFixtureByIndex(fixtureIndex)) {
		b2Filter filter;
		filter.categoryBits = categoryBits;
		filter.maskBits = maskBits;
		filter.groupIndex = groupIndex;
		fixture->SetFilterData(filter);
	}
}

size_t PhysBody::GetFixtureCount() const {
	size_t count = 0;
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
		++count;
	}
	return count;
}


void PhysBody::DestroyBody() {
	if (body && body->GetWorld()) {
		body->GetWorld()->DestroyBody(body);
		body = nullptr;
	}
}

#pragma endregion