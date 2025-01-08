#pragma once
#include <vector>
#include "raylib.h"
class Pilot;
class SceneGame;
class UIRendererCPU
{
private:
	SceneGame* gameAt;
	Texture2D* texture = nullptr;
public:
	UIRendererCPU(SceneGame* GameAt);
	~UIRendererCPU();
	void Render();
};
