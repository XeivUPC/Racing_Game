#include "LapSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

LapSensor::LapSensor(Module* gameAt, Vector2 position, vector<Vector2> vertices, int order) : MapObject(gameAt)
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

LapSensor::~LapSensor()
{
}

update_status LapSensor::Update()
{
	if (sensor.OnTriggerEnter() && enabled) {
		OnTrigger();
	}
	return UPDATE_CONTINUE;
}

bool LapSensor::CleanUp()
{
	delete body;
	return true;
}

void LapSensor::Enable()
{
	enabled = true;
}

void LapSensor::Disable()
{
	enabled = false;
}

void LapSensor::Activate()
{
	activated = true;
}

void LapSensor::Deactivate()
{
	activated = false;
}

int LapSensor::GetOrder() const
{
	return order;
}

void LapSensor::OnTrigger()
{
	Activate();
}
