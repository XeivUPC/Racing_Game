#include "Wheel.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "Box2DFactory.h"
#include <raymath.h>
#include <set> 

Wheel::Wheel(Vehicle* owner, float radius, float width)
{
	this->owner = owner;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	ModulePhysics* physics = owner->GetModuleAt()->App->physics;
	const Box2DFactory& factory = physics->factory();
	body = factory.CreateBox({0,0}, width, radius*2, fixtureData);

	uint16 categoryBits = physics->VEHICLE_WHEEL_LAYER;
	uint16 maskBits = physics->FRICTION_AREA_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);
	body->SetBullet(true);

	sensor.SetFixtureToTrack(body,0);
	sensor.AcceptOnlyTriggers(true);
}

Wheel::~Wheel()
{
}

update_status Wheel::Update()
{
	UpdateTraction();
	UpdateFriction();
	return UPDATE_CONTINUE;
}

bool Wheel::CleanUp()
{
	if (joint != nullptr)
		delete joint;
	delete body;
	return false;
}

void Wheel::UpdateTraction()
{
	vector<PhysBody*> areas = sensor.GetBodiesColliding();
	if (areas.size() == 0)
		currentTraction = 1;
	else {
		currentTraction = 0;
		for (const auto& area : areas) {
			if (area->GetFriction(0) > currentTraction)
				currentTraction = area->GetFriction(0);
		}
	}
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

void Wheel::SetUpWheelRenderCharacteristics(Texture2D* wheelTexture, Rectangle wheelTextureRec, bool rendereable, bool rendersOverVehicle)
{
	this->wheelTexture = wheelTexture;
	this->wheelTextureRec = wheelTextureRec;
	this->rendereable = rendereable;
	this->rendersOverVehicle = rendersOverVehicle;
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


void Wheel::InstallJoint(PhysJoint* joint)
{
	this->joint = joint;
}

PhysJoint* Wheel::GetJoint()
{
	return joint;
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

void Wheel::Render()
{
	if (!rendereable)
		return;
	Vector2 wheelRotatedOffset = {
		-wheelTextureRec.width / 2,
		-wheelTextureRec.height / 2
	};

	double radianAngle = owner->GetRotation();
	double extraAngle = 0;
	if (GetJoint() != nullptr)
		extraAngle = GetJoint()->GetJointAngle();
	radianAngle += extraAngle;
	owner->GetModuleAt()->App->renderer->Draw(*wheelTexture, body->GetPhysicPosition(), wheelRotatedOffset, &wheelTextureRec, RAD2DEG * (radianAngle), 1.8f*3, (int)cos(-wheelRotatedOffset.x), (int)sin(-wheelRotatedOffset.y));
}
