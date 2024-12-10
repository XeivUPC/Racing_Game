#include "Car.h"
#include "Wheel.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2DFactory.h"

Car::Car(ModuleGame* gameAt) : Vehicle(gameAt)
{
	//// Create Wheels

    const Box2DFactory& factory = gameAt->App->physics->factory();
    body = factory.CreateBox({5,5},2,4);
    body->SetAngularDamping(3);
    body->SetDensity(0,0.4f);
    body->SetMass(100, {0,0},30);

    Wheel* wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    PhysJoint* jointBackL = factory.CreateRevoluteJoint(body, wheel->body, { -1.1f, -1.5f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    PhysJoint* jointBackR = factory.CreateRevoluteJoint(body, wheel->body, { 1.1f, -1.5f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointFrontL = factory.CreateRevoluteJoint(body, wheel->body, { -1, 1.5f }, {0,0}, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointFrontR = factory.CreateRevoluteJoint(body, wheel->body, { 1, 1.5f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);
}

Car::~Car()
{
}

update_status Car::Update()
{
	Vehicle::Update();

    Vector2 dir{0,0};
    if (IsKeyDown(KEY_W))
        dir.y += 1;

    if (IsKeyDown(KEY_S))
        dir.y -= 1;

   
    for (const auto& wheel : wheels)
    {
        wheel->Move(dir.y);        
    }


    //control steering
    float lockAngle = 35 * DEGTORAD;
    float turnSpeedPerSec = 160 * DEGTORAD;//from lock to lock in 0.5 sec
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;


    if (IsKeyDown(KEY_A))
        desiredAngle -= lockAngle;

    if (IsKeyDown(KEY_D))
        desiredAngle += lockAngle;

    float angleNow = jointFrontL->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    jointFrontL->SetLimits(newAngle, newAngle);
    jointFrontR->SetLimits(newAngle, newAngle);

	return UPDATE_CONTINUE;
}

bool Car::CleanUp()
{
	Vehicle::CleanUp();
	return true;
}
