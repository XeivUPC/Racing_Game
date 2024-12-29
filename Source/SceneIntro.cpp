#include "SceneIntro.h"
#include "SceneMainMenu.h"
#include "SceneGame.h"

#include "Application.h"
#include "ModuleRender.h"
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
	return UPDATE_CONTINUE;
}

bool SceneIntro::Render()
{
	Font font = App->assetLoader->basicFont;
	int fontSize = 100;
	std::string text = "Starting...";

	Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize,0);

	float xTextPos = App->window->GetLogicWidth()/2 - textSize.x/2;
	float yTextPos = App->window->GetRealHeight()/2 - textSize.y/2 ;


	App->renderer->DrawText(text.c_str(), {xTextPos, yTextPos}, {0,0}, font, fontSize, 0, RED);

	ModuleScene::FadeRender();
	return true;
}

bool SceneIntro::CleanUp()
{
	
	return true;
}
