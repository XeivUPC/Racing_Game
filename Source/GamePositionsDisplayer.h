#pragma once
#include <vector>
#include "raylib.h"
class Pilot;
class SceneGame;

class GamePositionsDisplayer
{
private:
	SceneGame* gameAt;
	Texture2D* texture = nullptr;
public:
	GamePositionsDisplayer(SceneGame* GameAt);
	~GamePositionsDisplayer();
	void Render();
};
