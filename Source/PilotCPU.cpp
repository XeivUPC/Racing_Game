#include "PilotCPU.h"
#include "Vehicle.h"
#include "SceneGame.h"
#include "Application.h"
#include "RaceTrack.h"
#include "MapLapSensor.h"
#include "Box2DFactory.h"
#include <string>
#include <cmath>
#include <raymath.h>

PilotCPU::PilotCPU(SceneGame* gameAt, RaceTrack* track, std::string vehicleType) : Pilot(gameAt, track, vehicleType)
{
    pilotName = "CPU";
    ModulePhysics* physics = moduleAt->App->physics;
    const Box2DFactory& factory = physics->factory();

    b2FixtureUserData fixtureData;
    vector<Vector2> vertices;
    int fixtureIndex = 0;

    /// Curve Prediction Sensors
    vertices = { {2,0},{4,10},{0,11},{-4,10},{-2,0} };
    fixtureData.pointer = (uintptr_t)(&curvePredictorSensor);
    fixtureIndex = factory.AddPolygon(vehicle->body, {0,5}, vertices, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER,0);
    curvePredictorSensor.SetFixtureToTrack(vehicle->body, fixtureIndex);

    fixtureData.pointer = (uintptr_t)(&curvePredictorHelperSensorLeft);
    fixtureIndex = factory.AddCircle(vehicle->body, {5,8 }, 0.5f, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER, 0);
    curvePredictorHelperSensorLeft.SetFixtureToTrack(vehicle->body, fixtureIndex);

    fixtureData.pointer = (uintptr_t)(&curvePredictorHelperSensorRight);
    fixtureIndex = factory.AddCircle(vehicle->body, {-5,8 }, 0.5f, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER, 0);
    curvePredictorHelperSensorRight.SetFixtureToTrack(vehicle->body, fixtureIndex);


    /// Curve Sensors
    vertices = { {0,0},{0,1},{0.8,0.8},{1,0} };
    fixtureData.pointer = (uintptr_t)(&leftCurveSensor);
    fixtureIndex = factory.AddPolygon(vehicle->body, { 1,3 }, vertices, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER, 0);
    leftCurveSensor.SetFixtureToTrack(vehicle->body, fixtureIndex);

    vertices = { {0,0},{0,2},{1.8, 1.8},{2,0} };
    fixtureData.pointer = (uintptr_t)(&leftCurveSensorFar);
    fixtureIndex = factory.AddPolygon(vehicle->body, { 1,3 }, vertices, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER, 0);
    leftCurveSensorFar.SetFixtureToTrack(vehicle->body, fixtureIndex);

    vertices = { {0,0},{0,1},{-0.8,0.8},{-1,0} };
    fixtureData.pointer = (uintptr_t)(&rightCurveSensor);
    fixtureIndex = factory.AddPolygon(vehicle->body, { -1,3 }, vertices, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER, 0);
    rightCurveSensor.SetFixtureToTrack(vehicle->body, fixtureIndex);

    vertices = { {0,0},{0,2},{-1.8, 1.8},{-2,0} };
    fixtureData.pointer = (uintptr_t)(&rightCurveSensorFar);
    fixtureIndex = factory.AddPolygon(vehicle->body, { -1,3 }, vertices, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER, 0);
    rightCurveSensorFar.SetFixtureToTrack(vehicle->body, fixtureIndex);


    //// Front Sensor
    fixtureData.pointer = (uintptr_t)(&frontSensor);
    fixtureIndex = factory.AddBox(vehicle->body, { 0,8 }, 4,0.5f, fixtureData);
    vehicle->body->SetSensor(fixtureIndex, true);
    vehicle->body->SetFilter(fixtureIndex, physics->VEHICLE_SENSOR_LAYER, physics->FRICTION_AREA_LAYER, 0);
    frontSensor.SetFixtureToTrack(vehicle->body, fixtureIndex);
}

PilotCPU::~PilotCPU()
{
}

update_status PilotCPU::Update()
{
	Brain();
	vehicle->SetInput(direction);
	vehicle->Update();

    printf("DEBUG CPU--> dirX = %f  /  dirY = %f\n", direction.x, direction.y);
	return UPDATE_CONTINUE;
}

void PilotCPU::Brain()
{
    float steering = 0;
    float throttle = 1;

    bool predictedCurve = false;
    if (curvePredictorSensor.IsBeingTriggered()) {
        predictedCurve = true;
        if (curvePredictorHelperSensorLeft.IsBeingTriggered())
            steering += 0.4f;
        if (curvePredictorHelperSensorRight.IsBeingTriggered())
            steering -= 0.4f;
    }

    if (leftCurveSensorFar.IsBeingTriggered()) {
        steering += 0.1f;
        if (leftCurveSensor.IsBeingTriggered()) {
            steering += 0.1f;
        }
    }

    if (rightCurveSensorFar.IsBeingTriggered()) {
        steering -= 0.1f;
        if (rightCurveSensor.IsBeingTriggered()) {
            steering -= 0.1f;
        }
    }

    if (frontSensor.IsBeingTriggered()) {
        throttle /= 5.f;
        steering += steering / 2;
    }


    direction = { steering, throttle };

    

}
