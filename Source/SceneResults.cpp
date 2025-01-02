#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneResults.h"
#include "SceneOptions.h"
#include "SceneMainMenu.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
#include "ModuleLocalization.h"

SceneResults::SceneResults(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

SceneResults::~SceneResults()
{
}

bool SceneResults::Start()
{
	LOG("Loading Main Menu assets");
	bool ret = true;

	// Background
	backgroundTexture = App->texture->GetTexture("UI_Bg");

	// Play Button
	// Texture
	next_buttonTexture_hover = App->texture->GetTexture("main_menu_play_hover");

	//Functionality
	next_button = new UIButton(this, { next_buttonTextureRec.x, next_buttonTextureRec.y }, { next_buttonTextureRec.width, next_buttonTextureRec.height });

	next_button->onMouseClick.emplace_back([&]() {ClickNext(); });
	next_button->onMouseOver.emplace_back([&]() {OnMouseOverNext(); });

	/* Play Audio */
	//App->audio->PlayMusic("Assets/Sounds/Music/Main_Menu.wav");

	StartFadeOut(BLACK, 0.3f);

	return ret;
}

update_status SceneResults::Update()
{
	if (!App->scene_options->IsEnabled()) {
		next_button->Update();
		FadeUpdate();

		Render();
	}


	return UPDATE_CONTINUE;
}

bool SceneResults::Render() {

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, { 0,0 }, &backgroundTextureRec, 0, 1);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
	App->renderer->BlockRenderLayer();
	if (App->localization->GetString("MAINMENU_PLAY").length() < 5) {
		App->renderer->DrawText("NEXT", { next_buttonTextureRec.x , next_buttonTextureRec.y }, { buttonsText_Offset.x + App->assetLoader->agencyB.recs->width, buttonsText_Offset.y }, App->assetLoader->agencyB, 100, 0, WHITE);
	}
	else {
		App->renderer->DrawText("NEXT", { next_buttonTextureRec.x , next_buttonTextureRec.y}, buttonsText_Offset, App->assetLoader->agencyB, 100, 0, WHITE);
	}

	App->renderer->UnlockRenderLayer();

	FadeRender();

	return true;
}

bool SceneResults::CleanUp()
{
	LOG("Unloading Main Menu");

	delete next_button;

	return true;
}

void SceneResults::ClickNext()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	StartFadeIn(App->scene_main_menu, BLACK, 0.3f);
	// Go to Play Scene
}

void SceneResults::OnMouseOverNext()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*next_buttonTexture_hover, { next_buttonTextureRec.x , next_buttonTextureRec.y }, { 0,0 }, &next_button_section, 0, 2);
}