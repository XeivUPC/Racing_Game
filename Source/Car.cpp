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
    body = factory.CreateBox({5,5},2.f,4.5f);
    body->SetAngularDamping(3);
    body->SetDensity(0,0.4f);
    body->SetMass(100, {0,0},30);

    Wheel* wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointBackL = factory.CreateRevoluteJoint(body, wheel->body, { -1.1f, -1.4f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointBackR = factory.CreateRevoluteJoint(body, wheel->body, { 1.1f, -1.4f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointFrontL = factory.CreateRevoluteJoint(body, wheel->body, { -1.1f, 1.2f }, {0,0}, true, 0, 0);
    wheels.push_back(wheel);
    wheel->InstallJoint(jointFrontL);

    wheel = new Wheel(this);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointFrontR = factory.CreateRevoluteJoint(body, wheel->body, { 1.1f, 1.2f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);
    wheel->InstallJoint(jointFrontR);
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

    Rectangle carRect = { 0,0,16, 25 };
    Rectangle wheelRect = { 0,0,3, 5 };

    double radianAngle = body->GetAngle();

    Vector2 carRotatedOffset = {
       (float)(cos(radianAngle) * carRect.width/2 - sin(radianAngle) * carRect.height / 2.f) ,
        (float)(sin(radianAngle) * carRect.width / 2 + cos(radianAngle) * carRect.height / 2.f)
    };
    

    radianAngle =0;
   

    for (const auto& wheel : wheels)
    {
        radianAngle = body->GetAngle();
        double extraAngle = 0;
        if (wheel->GetJoint() != nullptr)
            extraAngle = wheel->GetJoint()->GetJointAngle();
        radianAngle += extraAngle;

        Vector2 wheelRotatedOffset = {
             (float)(cos(radianAngle) * wheelRect.width / 2 - sin(radianAngle) * wheelRect.height / 2 ),
             (float)(sin(radianAngle) * wheelRect.width / 2 + cos(radianAngle) * wheelRect.height / 2)
        };
        gameAt->App->renderer->Draw(*wheelTexture, wheel->body->GetPhysicPosition(), wheelRotatedOffset, &wheelRect, RAD2DEG * (radianAngle) + 180,9, (int)cos(-wheelRotatedOffset.x), (int)sin(-wheelRotatedOffset.y));
    }

    radianAngle = body->GetAngle();
    gameAt->App->renderer->Draw(*carTexture, body->GetPhysicPosition(), carRotatedOffset, &carRect, RAD2DEG * radianAngle + 180,9, (int)cos(-carRotatedOffset.x), (int)sin(- carRotatedOffset.y));
   
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
