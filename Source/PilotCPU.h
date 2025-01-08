#pragma once

#include "Pilot.h"
#include "CollisionSensor.h"
#include <string>

class Vehicle;
class SceneGame;
struct Vector2;

class PilotCPU : public Pilot
{
public:
	PilotCPU(SceneGame* gameAt, RaceTrack* track, std::string vehicleType, Color color);
	~PilotCPU();
	update_status Update();
	void Brain();

private:
	
	Vector2 direction;

	CollisionSensor curvePredictorSensor;
	CollisionSensor curvePredictorHelperSensorLeft;
	CollisionSensor curvePredictorHelperSensorRight;

	CollisionSensor leftCurveSensor;
	CollisionSensor leftCurveSensorFar;
	CollisionSensor rightCurveSensor;
	CollisionSensor rightCurveSensorFar;

	CollisionSensor leftLateralSensor;
	CollisionSensor rightLateralSensor;

	CollisionSensor obstacleSensor;

	CollisionSensor carSensor;

	CollisionSensor frontSensor;

};
