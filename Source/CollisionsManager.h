#pragma once
#include "ModulePhysics.h"
#include <vector>

class CollisionSensor;

class CollisionsManager : public b2ContactListener {
public:
    CollisionsManager();
    ~CollisionsManager(); 

private:

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact)override;
};
