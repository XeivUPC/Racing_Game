#include "MapObject.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class Tree : public MapObject 
{
public:
	Tree(Module* moduleAt, Vector2 position);
	~Tree(){}

	update_status Update();
	bool Render();
	bool CleanUp();

	void Enable();
	void Disable();

	void Activate();
	void Deactivate();

	Vector2 GetPos();
	double GetRotation();

private:

	void OnTrigger();

	// Enabled determines wether the sensor can be interacted with
	bool enabled = false;
	// Activated determines wether the sensor has been triggered
	bool activated = false;

	PhysBody* body = nullptr;
	CollisionSensor sensor;

	Texture2D* treeTexture = nullptr;
	Rectangle  treeTextureRec = { 0, 0, 47, 63};

	float linearDamping = 2;
	float angularDamping = 1;
};