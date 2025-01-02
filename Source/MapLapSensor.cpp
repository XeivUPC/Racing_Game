#include "MapLapSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "RaceTRack.h"
#include "Pilot.h"

MapLapSensor::MapLapSensor(Module* moduleAt, Vector2 position, vector<Vector2> vertices,RaceTrack* track , int order) : MapObject(moduleAt)
{
	this->order = order;
	this->track = track;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	ModulePhysics* physics = moduleAt->App->physics;
	const Box2DFactory& factory = physics->factory();

	body = factory.CreatePolygon(position, vertices, fixtureData);
	body->SetType(PhysBody::BodyType::Static);
	body->SetSensor(0, true);
	body->SetDensity(0, 1.f);
	body->SetBullet(true);

	uint16 categoryBits = physics->LAP_SENSOR_LAYER;
	uint16 maskBits = physics->VEHICLE_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);

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
		Pilot* pilot = (Pilot*)body->GetFixtureUserData(0).pointer;
		if (pilot != nullptr)
		{
			if (order - 1 == pilot->CurrentCheckpoint() ){
				pilot->AddCheckpoint();
			}
			else if(order == 0 && pilot->CurrentCheckpoint() == track->GetTrackSensors().size()-1){
				pilot->AddLap();
			}
			
		}
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

int MapLapSensor::GetOrder() const
{
	return order;
}

