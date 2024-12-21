#include "MapLapSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

MapLapSensor::MapLapSensor(Module* moduleAt, Vector2 position, vector<Vector2> vertices, int order) : MapObject(gameAt)
{
	this->order = order;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	const Box2DFactory& factory = moduleAt->App->physics->factory();
	body = factory.CreateChain(position, vertices);
	body->SetType(PhysBody::BodyType::Static);
	body->SetSensor(0, true);
	body->SetDensity(0, 1.f);

	sensor.SetFixtureToTrack(body, 0);

	sensor.AcceptOnlyTriggers(false);

	Enable();
}

MapLapSensor::~MapLapSensor()
{
}

update_status MapLapSensor::Update()
{
	if (sensor.OnTriggerEnter() && enabled) {
		OnTrigger();
	}
	return UPDATE_CONTINUE;
}

bool MapLapSensor::CleanUp()
{
	delete body;
	return true;
}

void MapLapSensor::Enable()
{
	enabled = true;
}

void MapLapSensor::Disable()
{
	enabled = false;
}

void MapLapSensor::Activate()
{
	activated = true;
}

void MapLapSensor::Deactivate()
{
	activated = false;
}

int MapLapSensor::GetOrder() const
{
	return order;
}

void MapLapSensor::OnTrigger()
{
	Activate();
}
