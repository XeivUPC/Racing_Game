#include "PauseMenu.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAssetLoader.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleScene.h"
#include "SceneGame.h"
#include "SceneOptions.h"
#include "SceneMainMenu.h"
#include "UIButton.h"

PauseMenu::PauseMenu(Module* moduleat)
{
	moduleAt = moduleat;
}

PauseMenu::~PauseMenu()
{
}

bool PauseMenu::Start()
{
	texture = moduleAt->App->texture->GetTexture("pause_texture");
	resume = new UIButton(moduleAt, { 700,100 }, {200,100});
	resume->onMouseClick.emplace_back([&]() {Resume(); });

	settings = new UIButton(moduleAt, { 700,300}, { 200,100 });
	settings->onMouseClick.emplace_back([&]() {Settings(); });

	mainMenu = new UIButton(moduleAt, { 700,500 }, { 200,100 });
	mainMenu->onMouseClick.emplace_back([&]() {MainMenu(); });
	return true;
}

bool PauseMenu::Update()
{
	if(!paused)
		return true;
	resume->Update();
	settings->Update();
	mainMenu->Update();
	return true;
}

bool PauseMenu::Render()
{
	if(!paused || moduleAt->App->scene_options->IsEnabled())
		return true;
	moduleAt->App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	moduleAt->App->renderer->DrawSimpleRectangle(rect, { 255,255,255,125 });

	moduleAt->App->renderer->DrawSimpleRectangle(resume->bounds, { 255,0,0,255 });
	moduleAt->App->renderer->DrawSimpleRectangle(settings->bounds, { 255,0,0,255 });
	moduleAt->App->renderer->DrawSimpleRectangle(mainMenu->bounds, { 255,0,0,255 });
	//rect = /**/;
	//App->renderer->Draw(*texture, { resume->bounds.x, resume->bounds.y}, {0,0}, &rect, 0, 1);
	//rect = /**/;
	//App->renderer->Draw(*texture, { settings->bounds.x, resume->bounds.y}, {0,0}, &rect, 0, 1);
	//rect = /**/;
	//App->renderer->Draw(*texture, { mainMenu->bounds.x, resume->bounds.y}, {0,0}, &rect, 0, 1);
	moduleAt->App->renderer->UnlockRenderLayer();
}

bool PauseMenu::CleanUp()
{
	delete resume;
	delete settings;
	delete mainMenu;
	return true;
}

bool PauseMenu::IsPaused()
{
	return paused;
}

void PauseMenu::Pause()
{
	paused = true;
}

void PauseMenu::Resume()
{
	paused = false;
}

void PauseMenu::Settings()
{
	moduleAt->App->audio->PlayFx(moduleAt->App->assetLoader->audioMotorId);
	moduleAt->App->scene_game->StartFadeIn(moduleAt->App->scene_options, BLACK, 0.3f, true);
	// Go to Options Scene
}

void PauseMenu::MainMenu()
{
	moduleAt->App->audio->PlayFx(moduleAt->App->assetLoader->audioMotorId);
	moduleAt->App->scene_game->StartFadeIn(moduleAt->App->scene_main_menu, BLACK, 0.3f, false);
	// Go to Main Menu Scene
}
