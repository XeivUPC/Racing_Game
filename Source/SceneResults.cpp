#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneResults.h"
#include "SceneGame.h"
#include "SceneOptions.h"
#include "SceneMainMenu.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
#include "ModuleLocalization.h"
#include "Pilot.h"

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
	backgroundTexture = App->texture->GetTexture("results_Background");

	// Play Button
	// Texture
	next_buttonTexture_hover = App->texture->GetTexture("results_next_button");

	//Functionality
	next_button = new UIButton(this, { next_buttonTextureRec.x, next_buttonTextureRec.y }, { next_buttonTextureRec.width, next_buttonTextureRec.height });

	next_button->onMouseClick.emplace_back([&]() {ClickNext(); });
	next_button->onMouseOver.emplace_back([&]() {OnMouseOverNext(); });

	/* Play Audio */
	//App->audio->PlayMusic("Assets/Sounds/Music/Main_Menu.wav");

	for (auto* pilot : App->scene_game->GetRacePlacePositions()) {
		PilotDataResults data;
		data.name = pilot->GetPilotName();
		pilotDatas.push_back(data);
	}

	App->audio->PlayMusic("Assets/Sounds/Music/Results.wav");

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

	App->renderer->DrawText("NEXT", { SCREEN_WIDTH / 2 , next_buttonTextureRec.y }, { -MeasureTextEx(App->assetLoader->agencyB, "NEXT", 80, 0).x / 2 , buttonsText_Offset.y}, App->assetLoader->agencyB, 80, 0, WHITE);

	float increasing_offset = 0;
	int pos = 1;
	std::string text = "null";
	for (const auto& pilot : pilotDatas) {
		text = std::to_string(pos) + " - " + pilot.name;
		Color color = WHITE;
		switch (pos)
		{
		case 1:
			color = GOLD;
			break;
		case 2:
			color = LIGHTGRAY;
			break;
		case 3:
			color = BROWN;
			break;
		default:
			break;
		}
		App->renderer->DrawText(text.c_str(), pilotsPos, {-MeasureTextEx(App->assetLoader->agencyB, text.c_str(), 40, 0).x / 2, buttonsText_Offset.y + increasing_offset}, App->assetLoader->agencyB, 40, 0, color);
		increasing_offset += 55;
		pos++;
	}

	App->renderer->UnlockRenderLayer();

	FadeRender();

	return true;
}

bool SceneResults::CleanUp()
{
	LOG("Unloading Main Menu");

	pilotDatas.clear();
	delete next_button;

	return true;
}

void SceneResults::ClickNext()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	StartFadeIn(App->scene_main_menu, BLACK, 0.3f);
	pilotDatas.clear();
	// Go to Play Scene
}

void SceneResults::OnMouseOverNext()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*next_buttonTexture_hover, { next_buttonTextureRec.x , next_buttonTextureRec.y }, { 0,0 }, &next_button_section, 0, 1);
}