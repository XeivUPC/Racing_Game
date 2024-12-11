#include "Car.h"
#include "Wheel.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Box2DFactory.h"

Car::Car(ModuleGame* gameAt) : Vehicle(gameAt)
{
    carTexture = gameAt->App->texture->GetTexture("Car");
    wheelTexture = gameAt->App->texture->GetTexture("Wheel");


	//// Create Wheels

    const Box2DFactory& factory = gameAt->App->physics->factory();
    body = factory.CreateBox({5,5},1.5f,1.5f);
    body->SetAngularDamping(3);
    body->SetDensity(0,0.4f);
    body->SetMass(100, {0,0},30);

    Wheel* wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointBackL = factory.CreateRevoluteJoint(body, wheel->body, { -1.1f, -1.5f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointBackR = factory.CreateRevoluteJoint(body, wheel->body, { 1.1f, -1.5f }, { 0,0 }, true, 0, 0);
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

    //control steering
    float lockAngle = 35 * DEGTORAD;
    float turnSpeedPerSec = 160 * DEGTORAD;//from lock to lock in 0.5 sec
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;

    desiredAngle = moveInput.x * lockAngle;

    float angleNow = jointFrontL->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    jointFrontL->SetLimits(newAngle, newAngle);
    jointFrontR->SetLimits(newAngle, newAngle);

  /*jointBackR->SetLimits(-newAngle, -newAngle);
    jointBackL->SetLimits(-newAngle, -newAngle);*/

    Rectangle carRect = { 0,0,carTexture->width, carTexture->height };

    float radianAngle = body->GetAngle();
    Vector2 rotatedOffset = {
       cos(radianAngle) * carTexture->width/2 - sin(radianAngle) * carTexture->height / 2 ,
       sin(radianAngle) * carTexture->width / 2 + cos(radianAngle) * carTexture->height / 2
    };
    gameAt->App->renderer->Draw(*carTexture, body->GetPhysicPosition().x + rotatedOffset.x, body->GetPhysicPosition().y + rotatedOffset.y,&carRect,RAD2DEG * body->GetAngle() + 180, cos(- rotatedOffset.x), sin(- rotatedOffset.y));


    DrawCircle(body->GetPhysicPosition().x, body->GetPhysicPosition().y,1,RED);
	return UPDATE_CONTINUE;
}

bool Car::CleanUp()
{
    delete jointBackL;
    delete jointBackR;
    delete jointFrontL;
    delete jointFrontR;

	Vehicle::CleanUp();
	return true;
}
