#include "Vehicle.h"
#include "Wheel.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleAssetLoader.h"
#include "DriftParticle.h"
#include "ParticleSystem.h"
#include "Pilot.h"
#include <raymath.h>

#include <pugixml.hpp>

using namespace pugi;

Vehicle::Vehicle(Module* moduleAt, Pilot* pilot, string id, Color vehicleColor) : MapObject(moduleAt)
{
	this->pilot = pilot;
	this->vehicleColor = vehicleColor;
	CreateVehicle(id);
	//particleSystem = new ParticleSystem(moduleAt);
	engineTimer.Start();
	moduleAt->App->audio->PlayFx(moduleAt->App->assetLoader->audioEngineStartId);
}

Vehicle::~Vehicle()
{
}

update_status Vehicle::Update()
{
	//particleSystem->UpdateParticles();

	for (const auto& wheel : wheels)
	{
		wheel->Update();	
	}
	for (const auto& wheel : throttlingWheels)
	{
		wheel->Move(moveInput.y);
	}

	float lockAngle = 35 * DEGTORAD;
	float turnSpeedPerSec = 160 * DEGTORAD;
	float turnPerTimeStep = turnSpeedPerSec / 60.0f;
	float desiredAngle = 0;

	desiredAngle = moveInput.x * lockAngle;

	for (const auto& wheel : steeringWheels)
	{
		float angleNow = wheel->GetJoint()->GetJointAngle();
		float angleToTurn = desiredAngle - angleNow;
		angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
		float newAngle = angleNow + angleToTurn;
		wheel->GetJoint()->SetLimits(newAngle, newAngle);
	}

	float vehicleSpeed = Vector2Length(body->GetLinearVelocity());

	//if (carSpeed > 1)
	//{
	//	for (const auto& wheel : throttlingWheels)
	//	{
	//		particleSystem->AddParticle(new DriftParticle({ wheel->GetJoint()->GetPhysicPositionBodyB() }, body->GetAngle(), 1.5f));
	//		particleSystem->AddParticle(new DriftParticle({ wheel->GetJoint()->GetPhysicPositionBodyB() }, body->GetAngle(), 1.5f));
	//	}
	//}
	
	if (engineTimer.ReadSec() > 2.9) {
		moduleAt->App->audio->PlayFx(moduleAt->App->assetLoader->audioEngineId);
		engineTimer.Start();
	}
	
	engineTimer.Update();
	return UPDATE_CONTINUE;
}

bool Vehicle::Render()
{
	moduleAt->App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_4);
	double radianAngle = body->GetAngle();

	Vector2 vehicleRotatedOffset = {
	   -vehicleTextureRecColor.width / 2.f,
	   -vehicleTextureRecColor.height / 2.f
	};

	for (const auto& wheel : wheels)
	{
		if (!wheel->rendersOverVehicle)
			wheel->Render();
	}

	radianAngle = body->GetAngle();
	moduleAt->App->renderer->Draw(*vehicleTexture, body->GetPhysicPosition(), vehicleRotatedOffset, &vehicleTextureRecColor, RAD2DEG * radianAngle, 1.8f*2, (int)cos(-vehicleRotatedOffset.x), (int)sin(-vehicleRotatedOffset.y), vehicleColor);

	moduleAt->App->renderer->Draw(*vehicleTexture, body->GetPhysicPosition(), vehicleRotatedOffset, &vehicleTextureRecFixed, RAD2DEG * radianAngle, 1.8f*2, (int)cos(-vehicleRotatedOffset.x), (int)sin(-vehicleRotatedOffset.y));

	for (const auto& wheel : wheels)
	{
		if (wheel->rendersOverVehicle)
			wheel->Render();
	}
	moduleAt->App->renderer->UnlockRenderLayer();
	return true;
}

bool Vehicle::CleanUp()
{
	//delete particleSystem;
	for (const auto& wheel : wheels)
	{
		/// Do Clean Up
		wheel->CleanUp();
		delete wheel;
	}
	delete body;
	wheels.clear();
	throttlingWheels.clear();
	steeringWheels.clear();
	moduleAt->App->audio->StopFx(moduleAt->App->assetLoader->audioEngineStartId);
	moduleAt->App->audio->StopFx(moduleAt->App->assetLoader->audioEngineId);
	return true;
}

void Vehicle::SetInput(Vector2 input)
{
	moveInput = input;
}


void Vehicle::CreateVehicle(string id)
{
	xml_document vehiclesData;
	pugi::xml_parse_result result = vehiclesData.load_file("Assets/Data/vehicle_data.xml");
	if (result)
	{
		LOG("config.xml parsed without errors");
	}
	else
	{
		LOG("Error loading config.xml: %s", result.description());
		return;
	}

	xml_node vehicleNode = vehiclesData.child("vehicle").child(id.c_str());
	xml_node texture_node = vehicleNode.child("texture");
	xml_node properties_node = vehicleNode.child("properties");
	xml_node information_node = vehicleNode.child("information");

	////Load Information
	vehicleName = information_node.child("name").attribute("value").as_string();
	vehicleTitle = information_node.child("title").attribute("value").as_string();
	vehicleCreator = information_node.child("created-by").attribute("value").as_string();
	vehicleDescription = information_node.child("description").attribute("value").as_string();

	//// Create Textures
	std::string textureName = texture_node.attribute("name").as_string();
	Vector2 textureOffset = { texture_node.attribute("pos-x").as_float(),texture_node.attribute("pos-y").as_float() };
	Vector2 textureSize = { texture_node.attribute("size-x").as_float(),texture_node.attribute("size-y").as_float() };
	vehicleTexture = moduleAt->App->texture->GetTexture(textureName.c_str());
	vehicleTextureRecColor = { textureOffset.x,textureOffset.y,textureSize.x,textureSize.y };
	vehicleTextureRecFixed = { textureOffset.x,textureOffset.y+vehicleTextureRecColor.height,textureSize.x,textureSize.y };

	//// Create Car
	Vector2 size = { vehicleNode.attribute("size-x").as_float(), vehicleNode.attribute("size-y").as_float() };
	float inertia = vehicleNode.attribute("inertia").as_float();
	float mass = vehicleNode.attribute("mass").as_float();


	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(pilot);

	ModulePhysics* physics = moduleAt->App->physics;
	const Box2DFactory& factory = physics->factory();
	body = factory.CreateBox({ 5,5 }, size.x, size.y, fixtureData);
	body->SetAngularDamping(3);
	body->SetDensity(0, 0.4f);
	body->SetLinearDamping(0.1f);
	body->SetBullet(true);
	body->SetMass(mass, { 0,0 }, inertia);

	uint16 categoryBits = physics->VEHICLE_LAYER;
	uint16 maskBits = physics->BOUNDARY_LAYER | physics->LAP_SENSOR_LAYER | physics->VEHICLE_LAYER | physics->VEHICLE_SENSOR_LAYER | physics->OBSTACLE_LAYER;
	body->SetFilter(0, categoryBits, maskBits, 0);

	maxForwardSpeed = properties_node.child("max-forward-speed").attribute("value").as_float();
	maxBackwardSpeed = properties_node.child("max-backward-speed").attribute("value").as_float();

	//// Create Wheels
	for (xml_node wheel_node = vehicleNode.child("wheels").child("wheel"); wheel_node != NULL; wheel_node = wheel_node.next_sibling("wheel"))
	{
		Vector2 wheelSize = { wheel_node.attribute("radius").as_float(), wheel_node.attribute("width").as_float() };
		Vector2 wheelOffset = { wheel_node.attribute("offset-x").as_float(), wheel_node.attribute("offset-y").as_float() };
		bool canSteer = wheel_node.attribute("can-steer").as_bool();
		bool canThrottle = wheel_node.attribute("can-throttle").as_bool();

		xml_node wheel_properties_node = wheel_node.child("properties");
		float maxDriveForce = wheel_properties_node.child("max-drive-force").attribute("value").as_float();
		float maxLateralImpulse = wheel_properties_node.child("max-lateral-impulse").attribute("value").as_float();

		Wheel* wheel = new Wheel(this, wheelSize.x, wheelSize.y);
		wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, maxDriveForce, maxLateralImpulse);

		xml_node texture_node = wheel_node.child("texture");
		std::string textureName = texture_node.attribute("name").as_string();
		Vector2 texturePos = { texture_node.attribute("pos-x").as_float(),texture_node.attribute("pos-y").as_float() };
		Vector2 textureSize = { texture_node.attribute("size-x").as_float(),texture_node.attribute("size-y").as_float() };

		Texture2D* wheelTexture = moduleAt->App->texture->GetTexture(textureName.c_str());
		Rectangle wheelTextureRec = { texturePos.x,texturePos.y,textureSize.x,textureSize.y };

		bool rendereable = wheel_properties_node.child("rendereable").attribute("value").as_bool();
		bool renderOverVehicle = wheel_properties_node.child("renders-over-vehicle").attribute("value").as_bool();
		bool copyOwnerColor = texture_node.attribute("copyOwnerColor").as_bool();
		Color wheelColor = WHITE;
		if (copyOwnerColor)
			wheelColor = vehicleColor;
		wheel->SetUpWheelRenderCharacteristics(wheelTexture, wheelTextureRec, wheelColor, rendereable, renderOverVehicle);

		PhysJoint* joint = factory.CreateRevoluteJoint(body, wheel->body, wheelOffset, { 0,0 }, true, 0, 0);
		wheel->InstallJoint(joint);

		wheels.emplace_back(wheel);
		if (canThrottle)
			throttlingWheels.emplace_back(wheel);
		if (canSteer)
			steeringWheels.emplace_back(wheel);
	}
}
