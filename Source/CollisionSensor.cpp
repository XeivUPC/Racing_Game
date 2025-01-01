#include "CollisionSensor.h"

CollisionSensor::CollisionSensor()
{

}

CollisionSensor::~CollisionSensor()
{
    bodiesColliding.clear();
}

void CollisionSensor::SetFixtureToTrack(PhysBody* physBodyToTrack, size_t fixtureIndex)
{
    this->physBodyToTrack = physBodyToTrack;
    this->fixtureIndex = fixtureIndex;
}

bool CollisionSensor::IsBeingTriggered()
{
    return bodiesInside!=0;
}

void CollisionSensor::AcceptOnlyTriggers(bool acceptOnlyTriggers)
{
    onlyTriggers = acceptOnlyTriggers;
}

bool CollisionSensor::OnTriggerEnter()
{
    if (lastBodyEnter != nullptr) {
        lastBodyEnter = nullptr;
        return true;
    }
    return false;
}

bool CollisionSensor::OnTriggerExit()
{
    if (lastBodyExit != nullptr) {
        lastBodyExit = nullptr;
        return true;
    }
    return nullptr;
}

PhysBody* CollisionSensor::OnTriggerEnterGet()
{
    if (lastBodyEnter != nullptr) {
        PhysBody* aux = lastBodyEnter;
        lastBodyEnter = nullptr;
        return aux;
    }
    return nullptr;
}

PhysBody* CollisionSensor::OnTriggerExitGet()
{
    if (lastBodyExit != nullptr) {
        PhysBody* aux = lastBodyExit;
        lastBodyExit = nullptr;
        return aux;
    }
    return nullptr;
}


void CollisionSensor::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Fixture* fixtureToTrack = &physBodyToTrack->body->GetFixtureList()[fixtureIndex];
    if (fixtureA == fixtureToTrack || fixtureB == fixtureToTrack) {
        if (!onlyTriggers || fixtureA->IsSensor() || fixtureB->IsSensor()) {
            bodiesInside++;
            PhysBody* bodyA = (PhysBody*)fixtureA->GetBody()->GetUserData().pointer;
            PhysBody* bodyB = (PhysBody*)fixtureB->GetBody()->GetUserData().pointer;
            lastBodyEnter = GetDifferentBody(bodyA, bodyB, physBodyToTrack);
            bodiesColliding.emplace(lastBodyEnter);
        }
    }
}

void CollisionSensor::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Fixture* fixtureToTrack = &physBodyToTrack->body->GetFixtureList()[fixtureIndex];
    if (fixtureA == fixtureToTrack || fixtureB == fixtureToTrack) {
        if (!onlyTriggers || fixtureA->IsSensor() || fixtureB->IsSensor()) {
            bodiesInside--;
            PhysBody* bodyA = (PhysBody*)fixtureA->GetBody()->GetUserData().pointer;
            PhysBody* bodyB = (PhysBody*)fixtureB->GetBody()->GetUserData().pointer;
            lastBodyExit = GetDifferentBody(bodyA, bodyB, physBodyToTrack);
            bodiesColliding.erase(lastBodyEnter);
        }
    }
}

std::set<PhysBody*> CollisionSensor::GetBodiesColliding()
{
    return bodiesColliding;
}

PhysBody* CollisionSensor::GetDifferentBody(PhysBody* body1, PhysBody* body2, PhysBody* bodyToBeDifferentFrom)
{
    if (body1 != bodyToBeDifferentFrom)
        return body1;
    return body2;
}


