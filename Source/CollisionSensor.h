#pragma once
#include "ModulePhysics.h"
#include <vector>

class PhysBody;

class CollisionSensor
{
public:
    CollisionSensor();
    ~CollisionSensor();
    void SetFixtureToTrack(PhysBody* physBodyToTrack, size_t fixtureIndex);
    bool IsBeingTriggered();
    void AcceptOnlyTriggers(bool acceptOnlyTriggers);
    bool OnTriggerEnter();
    bool OnTriggerExit();

    PhysBody* OnTriggerEnterGet();
    PhysBody* OnTriggerExitGet();


    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    std::vector<PhysBody*> GetBodiesColliding();
    
private:
    PhysBody* GetDifferentBody(PhysBody* body1, PhysBody* body2, PhysBody* bodyToBeDifferentFrom);
    
    PhysBody* physBodyToTrack =nullptr;
    b2Fixture* fixture;

    int bodiesInside = 0;
    bool onlyTriggers = true;

    PhysBody* lastBodyEnter=nullptr;
    PhysBody* lastBodyExit=nullptr;

    std::vector<PhysBody*> bodiesColliding;
};