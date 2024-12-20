#include "Car.h"
#include "Wheel.h"
#include <pugixml.hpp>
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "Box2DFactory.h"
#include "DriftParticle.h"
#include <raymath.h>

using namespace pugi;

Car::Car(Module* moduleAt) : Vehicle(moduleAt)
{
    particleSystem = new ParticleSystem(moduleAt);

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
   
    xml_node vehicleNode = vehiclesData.child("vehicle").child("car-type1");
    xml_node texture_node = vehicleNode.child("textures");
    xml_node properties_node = vehicleNode.child("properties");

    //// Create Textures
    std::string textureName = texture_node.child("vehicle-texture").attribute("name").as_string();
    Vector2 textureOffset = { texture_node.child("vehicle-texture").attribute("offset-x").as_float(),texture_node.child("vehicle-texture").attribute("offset-y").as_float() };
    Vector2 textureSize = { texture_node.child("vehicle-texture").attribute("size-x").as_float(),texture_node.child("vehicle-texture").attribute("size-y").as_float() };
    carTexture = moduleAt->App->texture->GetTexture(textureName.c_str());
    carTextureRec = { textureOffset.x,textureOffset.y,textureSize.x,textureSize.y };

    textureName = texture_node.child("wheel-texture").attribute("name").as_string();
    textureOffset = { texture_node.child("wheel-texture").attribute("offset-x").as_float(),texture_node.child("wheel-texture").attribute("offset-y").as_float() };
    textureSize = { texture_node.child("wheel-texture").attribute("size-x").as_float(),texture_node.child("wheel-texture").attribute("size-y").as_float() };
    wheelTexture = moduleAt->App->texture->GetTexture(textureName.c_str());
    wheelTextureRec = { textureOffset.x,textureOffset.y,textureSize.x,textureSize.y };

	//// Create Car
    Vector2 size = { vehicleNode.attribute("size-x").as_float(), vehicleNode.attribute("size-y").as_float() };
    float inertia = vehicleNode.attribute("inertia").as_float();
    float mass = vehicleNode.attribute("mass").as_float();

    const Box2DFactory& factory = moduleAt->App->physics->factory();
    body = factory.CreateBox({5,5},size.x,size.y);
    body->SetAngularDamping(3);
    body->SetDensity(0,0.4f);
    body->SetMass(mass, {0,0},inertia);

    maxForwardSpeed = properties_node.child("max-forward-speed").attribute("value").as_float();
    maxBackwardSpeed = properties_node.child("max-backward-speed").attribute("value").as_float();
    backTireMaxDriveForce = properties_node.child("back-tire-max-drive-force").attribute("value").as_float();
    frontTireMaxDriveForce = properties_node.child("front-tire-max-drive-force").attribute("value").as_float();
    backTireMaxLateralImpulse = properties_node.child("back-tire-max-lateral-impulse").attribute("value").as_float();
    frontTireMaxLateralImpulse = properties_node.child("front-tire-max-lateral-impulse").attribute("value").as_float();

    //// Create Wheels
    for (xml_node wheelNode = vehicleNode.child("wheels").child("wheel"); wheelNode != NULL; wheelNode = wheelNode.next_sibling("wheel"))
    {
        Vector2 wheelSize = { wheelNode.attribute("radius").as_float(), wheelNode.attribute("width").as_float() };
        Vector2 wheelOffset = { wheelNode.attribute("offset-x").as_float(), wheelNode.attribute("offset-y").as_float() };
        bool canSteer = wheelNode.attribute("can-steer").as_bool();
        bool canThrottle = wheelNode.attribute("can-throttle").as_bool();
        bool isFrontWheel = wheelNode.attribute("is-front-wheel").as_bool();

        Wheel* wheel = new Wheel(this, wheelSize.x, wheelSize.y);
        if (isFrontWheel)
            wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
        else 
            wheel->SetUpWheelCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
      
        PhysJoint* joint = factory.CreateRevoluteJoint(body, wheel->body, wheelOffset, { 0,0 }, true, 0, 0);
        wheel->InstallJoint(joint);
        wheels.emplace_back(wheel);
        if (canThrottle)
            throttlingWheels.emplace_back(wheel);
        if (canSteer)
            steeringWheels.emplace_back(wheel);
    }
}

Car::~Car()
{
}

update_status Car::Update()
{
	Vehicle::Update();
    particleSystem->UpdateParticles();


    double radianAngle = body->GetAngle();

    Vector2 carRotatedOffset = {
       -carTextureRec.width/2.f,
       -carTextureRec.height / 2.f
    };
    Vector2 wheelRotatedOffset = {
             -wheelTextureRec.width / 2,
             -wheelTextureRec.height / 2
    };

    radianAngle =0;

    float carSpeed = Vector2Length(body->GetLinearVelocity());

    if (carSpeed > 1)
    {
        for (const auto& wheel : throttlingWheels)
        {
            particleSystem->AddParticle(new DriftParticle({ wheel->GetJoint()->GetPhysicPositionBodyB() }, body->GetAngle(), 1.5f));
            particleSystem->AddParticle(new DriftParticle({ wheel->GetJoint()->GetPhysicPositionBodyB() }, body->GetAngle(), 1.5f));
        }
    }

    for (const auto& wheel : wheels)
    {

        radianAngle = body->GetAngle();
        double extraAngle = 0;
        if (wheel->GetJoint() != nullptr)
            extraAngle = wheel->GetJoint()->GetJointAngle();
        radianAngle += extraAngle;
        moduleAt->App->renderer->Draw(*wheelTexture, wheel->body->GetPhysicPosition(), wheelRotatedOffset, &wheelTextureRec, RAD2DEG * (radianAngle), 9, (int)cos(-wheelRotatedOffset.x), (int)sin(-wheelRotatedOffset.y));
    }

    radianAngle = body->GetAngle();
    moduleAt->App->renderer->Draw(*carTexture, body->GetPhysicPosition(), carRotatedOffset, &carTextureRec, RAD2DEG * radianAngle ,9, (int)cos(-carRotatedOffset.x), (int)sin(- carRotatedOffset.y));
   
	return UPDATE_CONTINUE;
}

bool Car::CleanUp()
{
	Vehicle::CleanUp();
    delete particleSystem;
	return true;
}
