#include "Obstacle.h"
#include "CollisionSensor.h"

#include <vector>
#include <string>

class PhysBody;

class BreakableObstacle : public Obstacle
{
public:
	BreakableObstacle(Module* moduleAt, Vector2 position, Vector2 size);
	~BreakableObstacle() {}

	update_status Update();
	bool CleanUp();

private:


protected:
	void OnHit();
};