#include "Wheel.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2DFactory.h"
#include <raymath.h>

Wheel::Wheel(Vehicle* owner)
{
	this->owner = owner;

	const Box2DFactory& factory = owner->GetGameAt()->App->physics->factory();
	body = factory.CreateBox({0,0}, 0.5f, 1.25f);
}

Wheel::~Wheel()
{
}

update_status Wheel::Update()
{
	//UpdateTraction();
	UpdateFriction();
	return UPDATE_CONTINUE;
}

bool Wheel::CleanUp()
{
	delete body;
	return false;
}

void Wheel::UpdateTraction()
{
}

void Wheel::UpdateFriction()
{
	Vector2 impulse = Vector2Scale(GetLateralVelocity(), -body->GetMass());

	if (Vector2Length(impulse) > maxLateralImpulse) {
		impulse = Vector2Scale(impulse, maxLateralImpulse / Vector2Length(impulse));
	}
	body->ApplyLinearImpulse(Vector2Scale(impulse,currentTraction), body->GetWorldCenter());

	//angular velocity
	float angularImpulse = currentTraction * 0.1f * body->GetInertia() * -body->GetAngularVelocity();
	body->ApplyAngularImpulse(angularImpulse);

	//forward linear velocity
	Vector2 currentForwardNormal = GetForwardVelocity();
	float currentForwardSpeed = Vector2Length(Vector2Normalize(currentForwardNormal));
	float dragForceMagnitude = -2 * currentForwardSpeed;
	body->ApplyForce(Vector2Scale(currentForwardNormal,currentTraction * dragForceMagnitude), body->GetWorldCenter());

	
}

void Wheel::SetUpWheelCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse)
{
	this->maxForwardSpeed = maxForwardSpeed;
	this->maxBackwardSpeed = maxBackwardSpeed;
	this->maxDriveForce = maxDriveForce;
	this->maxLateralImpulse = maxLateralImpulse;
}

Vector2 Wheel::GetLateralVelocity()
{
	Vector2 currentRightNormal = body->GetWorldVector({ 1,0 });
	return Vector2Scale(currentRightNormal, Vector2DotProduct(currentRightNormal, body->GetLinearVelocity()));
}

Vector2 Wheel::GetForwardVelocity()
{
	Vector2 currentForwardNormal = body->GetWorldVector({ 0, 1 });
	return Vector2Scale(currentForwardNormal, Vector2DotProduct(currentForwardNormal, body->GetLinearVelocity()));
}


void Wheel::Turn(int direction)
{
	float desiredTorque = 0;

	desiredTorque = 7.f * direction;

	body->ApplyTorque(desiredTorque);
}

void Wheel::Move(int direction)
{
	//find current speed in forward direction
	Vector2 currentForwardNormal = body->GetWorldVector({ 0, 1 });
	float currentSpeed = Vector2DotProduct(GetForwardVelocity(), currentForwardNormal);


	//find desired speed
	float desiredSpeed = 0;
	if (direction == 1) {
		desiredSpeed = maxForwardSpeed;
	}
	else if(direction == -1){
		desiredSpeed = maxBackwardSpeed;
	}
	else
		desiredSpeed = currentSpeed;


	//apply necessary force
	float force = 0;
	if (desiredSpeed > currentSpeed)
		force = maxDriveForce;
	else if (desiredSpeed < currentSpeed)
		force = -maxDriveForce;
	else
		return;

	Vector2 forceVector = Vector2Scale(currentForwardNormal, currentTraction * force);
	body->ApplyForce(forceVector, body->GetWorldCenter());
}
