#include "SceneIntro.h"
#include "SceneMainMenu.h"
#include "SceneGame.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "ModuleWindow.h"
#include "ModuleAssetLoader.h"

SceneIntro::SceneIntro(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

}

SceneIntro::~SceneIntro()
{
}

bool SceneIntro::Start()
{
	intro_ended = false;
	BgTexture = App->texture->GetTexture("UI_Intro_Bg");
	return true;
}

update_status SceneIntro::Update()
{
	if (!intro_ended && intro_timer.ReadSec() > intro_duration) {
		intro_ended = true;
		StartFadeIn(App->scene_main_menu,BLACK, 0.5f);
	}
	ModuleScene::FadeUpdate();
	Render();
	intro_timer.Update();
	return UPDATE_CONTINUE;
}

bool SceneIntro::Render()
{

	App->renderer->Draw(*BgTexture, { 0,0 }, {0,0});

	ModuleScene::FadeRender();
	return true;
}

bool SceneIntro::CleanUp()
{
	
	return true;
}
