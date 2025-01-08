#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneMainMenu.h"
#include "SceneSelectSetup.h"
#include "SceneOptions.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
#include "ModuleLocalization.h"

SceneMainMenu::SceneMainMenu(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

SceneMainMenu::~SceneMainMenu()
{
}

bool SceneMainMenu::Start()
{
	LOG("Loading Main Menu assets");
	bool ret = true;
	// Background
	backgroundTexture = App->texture->GetTexture("UI_MainMenu_Bg");


	// Play Button
	// Texture
	btn_texture = App->texture->GetTexture("UI_Btn1");
	
	//Functionality

	Vector2 posOffset = { SCREEN_WIDTH / 2 - btn_rect.width / 2.f,SCREEN_HEIGHT / 2 - btn_rect.height / 2.f + 100 };

	play_button = new UIButton(this, { posOffset.x, posOffset.y }, { btn_rect.width,btn_rect.height });
	
	play_button->onMouseClick.emplace_back([&]() {ClickPlay(); });

	// Settings Button
	//Functionality
	settings_button = new UIButton(this, { posOffset.x, posOffset.y+100 }, { btn_rect.width,btn_rect.height });

	settings_button->onMouseClick.emplace_back([&]() {ClickSettings(); });

	/* Play Audio */
	App->audio->PlayMusic("Assets/Sounds/Music/Main_Menu.wav");

	StartFadeOut(BLACK, 0.3f);

	return ret;
}

update_status SceneMainMenu::Update()
{
	if (!App->scene_options->IsEnabled()) {
		play_button->Update();
		settings_button->Update();

		FadeUpdate();

		Render();
	}


	return UPDATE_CONTINUE;
}

bool SceneMainMenu::Render() {

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, { 0,0 }, &backgroundTextureRec, 0, 2);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
	App->renderer->BlockRenderLayer();


	switch (play_button->GetState())
	{
		case UIButton::BUTTON_STATE::NORMAL:
			App->renderer->Draw(*btn_texture, { play_button->bounds.x , play_button->bounds.y }, { 0,0 }, &btn_rect, 0, 1);
			break;
		case UIButton::BUTTON_STATE::OVER:
			App->renderer->Draw(*btn_texture, { play_button->bounds.x , play_button->bounds.y }, { 0,0 }, &btn_rect_hover, 0, 1);
			break;	
		case UIButton::BUTTON_STATE::PRESSED:
			App->renderer->Draw(*btn_texture, { play_button->bounds.x , play_button->bounds.y }, { 0,0 }, &btn_rect_pressed, 0, 1);
			break;
		default:
			App->renderer->Draw(*btn_texture, { play_button->bounds.x , play_button->bounds.y }, { 0,0 }, &btn_rect_pressed, 0, 1);
			break;
	}

	switch (settings_button->GetState())
	{
	case UIButton::BUTTON_STATE::NORMAL:
		App->renderer->Draw(*btn_texture, { settings_button->bounds.x , settings_button->bounds.y }, { 0,0 }, &btn_rect, 0, 1);
		break;
	case UIButton::BUTTON_STATE::OVER:
		App->renderer->Draw(*btn_texture, { settings_button->bounds.x , settings_button->bounds.y }, { 0,0 }, &btn_rect_hover, 0, 1);
		break;
	case UIButton::BUTTON_STATE::PRESSED:
		App->renderer->Draw(*btn_texture, { settings_button->bounds.x , settings_button->bounds.y }, { 0,0 }, &btn_rect_pressed, 0, 1);
		break;
	default:
		App->renderer->Draw(*btn_texture, { settings_button->bounds.x , settings_button->bounds.y }, { 0,0 }, &btn_rect_pressed, 0, 1);
		break;
	}

	string text = App->localization->GetString("MAINMENU_PLAY");
	Vector2 textSize = MeasureTextEx(App->assetLoader->agencyB, text.c_str(), 40, 0);
	Vector2 textPos = { play_button->bounds.x + play_button->bounds.width / 2.f - textSize.x / 2.f, play_button->bounds.y + play_button->bounds.height / 2 - textSize.y / 2 };
	App->renderer->DrawText(text.c_str(), textPos, { 0,0 }, App->assetLoader->agencyB, 40, 0, BLACK);



	text = App->localization->GetString("MAINMENU_SETTINGS");
	textSize = MeasureTextEx(App->assetLoader->agencyB, text.c_str(), 40, 0);
	textPos = { settings_button->bounds.x + settings_button->bounds.width/2.f - textSize.x / 2.f, settings_button->bounds.y + settings_button->bounds.height/2 - textSize.y / 2 };
	App->renderer->DrawText(text.c_str(), textPos, {0,0}, App->assetLoader->agencyB, 40, 0, BLACK);
	App->renderer->UnlockRenderLayer();

	FadeRender();

	return true;
}

bool SceneMainMenu::CleanUp()
{
	LOG("Unloading Main Menu");

	delete play_button;
	delete settings_button;

	return true;
}

void SceneMainMenu::ClickPlay()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	StartFadeIn(App->scene_select_setup, BLACK, 0.3f);
	// Go to Play Scene
}

void SceneMainMenu::ClickSettings()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	StartFadeIn(App->scene_options, BLACK, 0.3f, true);
	// Go to Options Scene
}
