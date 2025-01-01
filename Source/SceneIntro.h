#pragma once

#include "ModuleScene.h"

class SceneIntro : public ModuleScene
{
public:
	SceneIntro(Application * app, bool start_enabled = true);
	~SceneIntro();

	bool Start();
	update_status Update();
	bool Render();
	bool CleanUp();

public:

private:
	Texture* logoTexture = nullptr;
	Texture* BgTexture = nullptr;

	Timer intro_timer;
	float intro_duration = 2;

	bool intro_ended = false;
};

