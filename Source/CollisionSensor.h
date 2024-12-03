#pragma once
#include "ModulePhysics.h"
#include <set>

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

    std::set<PhysBody*> GetBodiesColliding();
    
private:
    PhysBody* GetDifferentBody(PhysBody* body1, PhysBody* body2, PhysBody* bodyToBeDifferentFrom);
    
    PhysBody* physBodyToTrack =nullptr;
    size_t fixtureIndex = 0;

    int bodiesInside = 0;
    bool onlyTriggers = true;

    PhysBody* lastBodyEnter=nullptr;
    PhysBody* lastBodyExit=nullptr;

    std::set<PhysBody*> bodiesColliding;
};