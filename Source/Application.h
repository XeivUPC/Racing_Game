#pragma once

#include "Globals.h"
#include "Timer.h"
#include <vector>

class Module;
class ModuleWindow;
class ModuleRender;
class ModuleAudio;
class ModuleTexture;
class ModuleLocalization;
class ModuleAssetLoader;
class ModulePhysics;

class SceneGame;
class SceneOptions;
class SceneMainMenu;
class SceneSelectSetup;
class SceneIntro;

class Application
{
public:

	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleAudio* audio;
	ModuleTexture* texture;
	ModuleLocalization* localization;
	ModuleAssetLoader* assetLoader;
	ModulePhysics* physics;

	SceneOptions* scene_options;
	SceneMainMenu* scene_main_menu;
	SceneSelectSetup* scene_select_setup;
	SceneGame* scene_game;
	SceneIntro* scene_intro;

private:

	std::vector<Module*> list_modules;
    uint64 frame_count = 0;

	Timer ptimer;
	Timer startup_time;
	Timer frame_time;
	Timer last_sec_frame_time;

	uint32 last_sec_frame_count = 0;
	uint32 prev_last_sec_frame_count = 0;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* module);
};