#include "MapLapSensor.h"
#include "MapLapSensorController.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Pilot.h"

MapLapSensor::MapLapSensor(Module* moduleAt, Vector2 position, vector<Vector2> vertices, int order) : MapObject(moduleAt)
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
	PhysBody* body = sensor.OnTriggerEnterGet();
	if (body != nullptr && enabled) {
		Pilot* pilot = (Pilot*)body->body->GetUserData().pointer;
		if (pilot != nullptr)
			controller->CrossCheckpoint(pilot, order);
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

void MapLapSensor::AddController(MapLapSensorController* lapcontroller)
{
	controller = lapcontroller;
}


int MapLapSensor::GetOrder() const
{
	return order;
}

