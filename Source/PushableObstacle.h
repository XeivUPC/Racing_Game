#include "Obstacle.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class PushableObstacle : public Obstacle
{
public:
	PushableObstacle(Module* moduleAt, Vector2 position, Vector2 size,float linearDamping, float angularDamping);
	~PushableObstacle() {}

	update_status Update();
	bool CleanUp();

private:
	

protected:
	void OnHit();

	float linearDamping = 1; 
	float angularDamping = 1; 
};