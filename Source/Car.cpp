#include "Car.h"
#include "Wheel.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Box2DFactory.h"
#include "DriftParticle.h"
#include <raymath.h>

Car::Car(Module* moduleAt) : Vehicle(moduleAt)
{
    carTexture = moduleAt->App->texture->GetTexture("Car");
    wheelTexture = moduleAt->App->texture->GetTexture("Wheel");

    particleSystem = new ParticleSystem(moduleAt);

    //animatorWheel = new Animator(moduleAt->App);

    //AnimationData wheelAnim = AnimationData("Wheel");
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{0, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{1, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{2, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{3, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{4, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{5, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{6, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{7, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{8, 0}, {3,5} });
    //wheelAnim.AddSprite(Sprite{ wheelTexture,{9, 0}, {3,5} });
    //animatorWheel->AddAnimation(wheelAnim);
    //animatorWheel->SelectAnimation("Wheel",true);
    //animatorWheel->SetSpeed(0.1f);

	//// Create Wheels

    const Box2DFactory& factory = moduleAt->App->physics->factory();
    body = factory.CreateBox({5,5},2.f,4.5f);
    body->SetAngularDamping(3);
    body->SetDensity(0,0.4f);
    body->SetMass(100, {0,0},30);

    Wheel* wheel = new Wheel(this,0.5f,0.5f);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointBackL = factory.CreateRevoluteJoint(body, wheel->body, { -1.1f, -1.5f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this, 0.5f, 0.5f);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointBackR = factory.CreateRevoluteJoint(body, wheel->body, { 1.1f, -1.5f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);

    wheel = new Wheel(this, 0.5f, 0.5f);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointFrontL = factory.CreateRevoluteJoint(body, wheel->body, { -1.f, 1.45f }, {0,0}, true, 0, 0);
    wheels.push_back(wheel);
    wheel->InstallJoint(jointFrontL);

    wheel = new Wheel(this, 0.5f, 0.5f);
    wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointFrontR = factory.CreateRevoluteJoint(body, wheel->body, { 1.f, 1.45f }, { 0,0 }, true, 0, 0);
    wheels.push_back(wheel);
    wheel->InstallJoint(jointFrontR);
}

Car::~Car()
{
}

update_status Car::Update()
{
	Vehicle::Update();
    particleSystem->UpdateParticles();

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

    Rectangle carRect = { 32,0,16, 28 };
    Rectangle wheelRect = { 3,0,3, 5 };

    double radianAngle = body->GetAngle();

    Vector2 carRotatedOffset = {
       -carRect.width/2.f,
       -carRect.height / 2.f
    };
    Vector2 wheelRotatedOffset = {
             -wheelRect.width / 2,
             -wheelRect.height / 2
    };

    radianAngle =0;


    float carSpeed = Vector2Length(body->GetLinearVelocity());

    if (carSpeed > 1)
    {
        particleSystem->AddParticle(new DriftParticle({jointBackL->GetPhysicPositionBodyB()}, body->GetAngle(), 1.5f));
        particleSystem->AddParticle(new DriftParticle({ jointBackR->GetPhysicPositionBodyB()}, body->GetAngle(), 1.5f));
    }

    //carSpeed *= 5;
    //carSpeed = ( maxForwardSpeed/ carSpeed) / 100;
    //animatorWheel->SetSpeed(carSpeed);
    //animatorWheel->Update();


    for (const auto& wheel : wheels)
    {

        radianAngle = body->GetAngle();
        double extraAngle = 0;
        if (wheel->GetJoint() != nullptr)
            extraAngle = wheel->GetJoint()->GetJointAngle();
        radianAngle += extraAngle;

        //animatorWheel->Animate(wheel->body->GetPhysicPosition(), wheelRotatedOffset, RAD2DEG * radianAngle + 180,9);
        moduleAt->App->renderer->Draw(*wheelTexture, wheel->body->GetPhysicPosition(), wheelRotatedOffset, &wheelRect, RAD2DEG * (radianAngle), 9, (int)cos(-wheelRotatedOffset.x), (int)sin(-wheelRotatedOffset.y));
    }

    radianAngle = body->GetAngle();
    moduleAt->App->renderer->Draw(*carTexture, body->GetPhysicPosition(), carRotatedOffset, &carRect, RAD2DEG * radianAngle ,9, (int)cos(-carRotatedOffset.x), (int)sin(- carRotatedOffset.y));
   
	return UPDATE_CONTINUE;
}

bool Car::CleanUp()
{
    delete jointBackL;
    delete jointBackR;
    delete jointFrontL;
    delete jointFrontR;

	Vehicle::CleanUp();

    //delete animatorWheel;
    delete particleSystem;
	return true;
}
