#include "PauseMenu.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAssetLoader.h"
#include "ModuleLocalization.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
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
	bg_texture = moduleAt->App->texture->GetTexture("UI_Pause_Bg");
	btn_texture = moduleAt->App->texture->GetTexture("UI_Btn1");

	Vector2 posOffset = { SCREEN_WIDTH / 2 -btn_rect.width/2.f,SCREEN_HEIGHT / 2 -btn_rect.height / 2.f };


	resume = new UIButton(moduleAt, { posOffset.x,posOffset.y - 100 }, { btn_rect.width,btn_rect.height});
	resume->onMouseClick.emplace_back([&]() {Resume(); });

	settings = new UIButton(moduleAt, { posOffset.x,posOffset.y + 40}, { btn_rect.width,btn_rect.height });
	settings->onMouseClick.emplace_back([&]() {Settings(); });

	mainMenu = new UIButton(moduleAt, { posOffset.x, posOffset.y + 180 }, { btn_rect.width,btn_rect.height });
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
	if (!paused || moduleAt->App->scene_options->IsEnabled())
		return true;
	moduleAt->App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_2);
	moduleAt->App->renderer->SetCameraMode(false);

	moduleAt->App->renderer->Draw(*bg_texture, { 0,0 }, { 0,0 });


	string titleText = moduleAt->App->localization->GetString("PAUSEMENU_TITLE");
	Vector2 textSize = MeasureTextEx(moduleAt->App->assetLoader->agencyB, titleText.c_str(), 80, 0);
	moduleAt->App->renderer->DrawText(titleText.c_str(), {SCREEN_WIDTH / 2 - textSize.x / 2,100}, {0,0}, moduleAt->App->assetLoader->agencyB, 80, 0, WHITE);
	
	switch (resume->GetState())
	{
		case UIButton::BUTTON_STATE::NORMAL:
			moduleAt->App->renderer->Draw(*btn_texture, { resume->bounds.x, resume->bounds.y }, { 0,0 },&btn_rect);
			break;
		case UIButton::BUTTON_STATE::OVER:
			moduleAt->App->renderer->Draw(*btn_texture, { resume->bounds.x, resume->bounds.y }, { 0,0 }, &btn_rect_hover);
			break;
		case UIButton::BUTTON_STATE::PRESSED:
			moduleAt->App->renderer->Draw(*btn_texture, { resume->bounds.x, resume->bounds.y }, { 0,0 }, &btn_rect_pressed);
			break;
		default:
			break;
	}
	string btnText = moduleAt->App->localization->GetString("PAUSEMENU_CONTINUE");
	textSize = MeasureTextEx(moduleAt->App->assetLoader->agencyB, btnText.c_str(), 35, 0);
	moduleAt->App->renderer->DrawText(btnText.c_str(), { SCREEN_WIDTH / 2 - textSize.x / 2, resume->bounds.y + textSize.y/2 }, { 0,0 }, moduleAt->App->assetLoader->agencyB, 35, 0, BLACK);
	
	switch (settings->GetState())
	{
	case UIButton::BUTTON_STATE::NORMAL:
		moduleAt->App->renderer->Draw(*btn_texture, { settings->bounds.x, settings->bounds.y }, { 0,0 }, &btn_rect);
		break;
	case UIButton::BUTTON_STATE::OVER:
		moduleAt->App->renderer->Draw(*btn_texture, { settings->bounds.x, settings->bounds.y }, { 0,0 }, &btn_rect_hover);
		break;
	case UIButton::BUTTON_STATE::PRESSED:
		moduleAt->App->renderer->Draw(*btn_texture, { settings->bounds.x, settings->bounds.y }, { 0,0 }, &btn_rect_pressed);
		break;
	default:
		break;
	}
	btnText = moduleAt->App->localization->GetString("MAINMENU_SETTINGS");
	textSize = MeasureTextEx(moduleAt->App->assetLoader->agencyB, btnText.c_str(), 35, 0);
	moduleAt->App->renderer->DrawText(btnText.c_str(), { SCREEN_WIDTH / 2 - textSize.x / 2, settings->bounds.y + textSize.y / 2 }, { 0,0 }, moduleAt->App->assetLoader->agencyB, 35, 0, BLACK);

	switch (mainMenu->GetState())
	{
	case UIButton::BUTTON_STATE::NORMAL:
		moduleAt->App->renderer->Draw(*btn_texture, { mainMenu->bounds.x, mainMenu->bounds.y }, { 0,0 }, &btn_rect);
		break;
	case UIButton::BUTTON_STATE::OVER:
		moduleAt->App->renderer->Draw(*btn_texture, { mainMenu->bounds.x, mainMenu->bounds.y }, { 0,0 }, &btn_rect_hover);
		break;
	case UIButton::BUTTON_STATE::PRESSED:
		moduleAt->App->renderer->Draw(*btn_texture, { mainMenu->bounds.x, mainMenu->bounds.y }, { 0,0 }, &btn_rect_pressed);
		break;
	default:
		break;
	}
	btnText = moduleAt->App->localization->GetString("PAUSEMENU_MAINMENU");
	textSize = MeasureTextEx(moduleAt->App->assetLoader->agencyB, btnText.c_str(), 35, 0);
	moduleAt->App->renderer->DrawText(btnText.c_str(), { SCREEN_WIDTH / 2 - textSize.x / 2, mainMenu->bounds.y + textSize.y / 2 }, { 0,0 }, moduleAt->App->assetLoader->agencyB, 35, 0, BLACK);


	moduleAt->App->renderer->SetCameraMode(true);
	moduleAt->App->renderer->UnlockRenderLayer();

	return true;
}

bool PauseMenu::CleanUp()
{
	Resume();
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
	moduleAt->App->audio->PlayFx(moduleAt->App->assetLoader->audioMotorId);
	paused = true;
	moduleAt->App->physics->PauseSimulation();
}

void PauseMenu::Resume()
{
	paused = false;
	moduleAt->App->physics->StartSimulation();
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
	moduleAt->App->scene_game->StartFadeIn(moduleAt->App->scene_main_menu, BLACK, 0.3f);
	// Go to Main Menu Scene
}
