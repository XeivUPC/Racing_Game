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
	virtual bool Render();
	virtual bool CleanUp();

	void StartFadeIn(ModuleScene* target, Color color, float time, bool additiveLoad = false);
	void StartFadeOut(Color color, float time);

	void FadeUpdate();
	virtual void FadeRender();

private:
	void FadeIn();
	void FadeOut();


	Timer fadeTimer;
	float fadeTime = -1;

	ModuleScene* fadeTarget = nullptr;
	bool unloadOnFade = false;

	bool doingFadeIn = false;
	bool doingFadeOut = false;

	Color fadeColor = WHITE;
};
