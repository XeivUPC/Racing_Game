#pragma once

#include "Module.h"
#include "Timer.h"

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	virtual bool Start();
	virtual update_status Update();
	virtual bool CleanUp();

	void StartFadeIn(ModuleScene* target, Color color, float time);
	void StartFadeOut(Color color, float time);

	void FadeUpdate();

private:
	void FadeIn();
	void FadeOut();

	Timer fadeTimer;
	float fadeTime = -1;

	ModuleScene* fadeTarget = nullptr;

	bool doingFadeIn = false;
	bool doingFadeOut = false;

	Color fadeColor = WHITE;
};
