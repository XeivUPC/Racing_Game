#include "SceneSelectSetup.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneMainMenu.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
#include "SceneOptions.h"
#include "ModuleLocalization.h"

SceneSelectSetup::SceneSelectSetup(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

SceneSelectSetup::~SceneSelectSetup()
{
}

bool SceneSelectSetup::Start()
{
	LOG("Loading Select Setup assets");
	bool ret = true;

	// Background
	App->texture->CreateTexture("Assets/Textures/select_setup_background.png", "select_setup");
	backgroundTexture = App->texture->GetTexture("select_setup");

	// Select Buttons
	// Texture
	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons.png", "select_setup_mode_buttons");
	buttons_texture = App->texture->GetTexture("select_setup_mode_buttons");

	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons_hover.png", "select_setup_mode_buttons_hover");
	buttons_texture_hover = App->texture->GetTexture("select_setup_mode_buttons_hover");

	// Race button
	race_button = new UIButton(this, { race_buttonTextureRec.x, race_buttonTextureRec.y }, { race_buttonTextureRec.width, race_buttonTextureRec.height });
	race_button->onMouseClick.emplace_back([&]() {ClickRACE(); });
	race_button->onMouseOver.emplace_back([&]() {OnMouseOverRACE(); });

	// Boom button
	boom_button = new UIButton(this, { boom_buttonTextureRec.x, boom_buttonTextureRec.y }, { boom_buttonTextureRec.width, boom_buttonTextureRec.height });
	boom_button->onMouseClick.emplace_back([&]() {ClickBOOM(); });
	boom_button->onMouseOver.emplace_back([&]() {OnMouseOverBOOM(); });

	// Car Selection
	//Texture
	App->texture->CreateTexture("Assets/Textures/select_setup_car_bg.png", "select_setup_car_bg");
	car_bg_texture = App->texture->GetTexture("select_setup_car_bg");

	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons_hover.png", "select_setup_mode_buttons_hover");
	finish_car_button_texture_hover = App->texture->GetTexture("select_setup_mode_buttons_hover");

	// Finish button
	finish_car_button = new UIButton(this, { finish_car_button_textureRec.x, finish_car_button_textureRec.y }, { finish_car_button_textureRec.width, finish_car_button_textureRec.height });
	finish_car_button->onMouseClick.emplace_back([&]() {ClickFINISH(); });
	finish_car_button->onMouseOver.emplace_back([&]() {OnMouseOverFINISH(); });

	// Right arrow button
	car_arrow_right = new UIButton(this, { car_arrow_right_rec.x, car_arrow_right_rec.y }, { car_arrow_right_rec.width, car_arrow_right_rec.height });
	car_arrow_right->onMouseClick.emplace_back([&]() {ClickCarRightArrow(); });

	// Left arrow button
	car_arrow_left = new UIButton(this, { car_arrow_left_rec.x, car_arrow_left_rec.y }, { car_arrow_left_rec.width, car_arrow_left_rec.height });
	car_arrow_left->onMouseClick.emplace_back([&]() {ClickCarLeftArrow(); });
	
	StartFadeOut(BLACK, 0.3f);

	return ret;
}

update_status SceneSelectSetup::Update()
{
	if (!isModeChosen) {
		race_button->Update();
		boom_button->Update();
	}
	if (!isCarChosen && isModeChosen) {
		finish_car_button->Update();
		car_arrow_right->Update();
		car_arrow_left->Update();
	}
	FadeUpdate();

	Render();
	return UPDATE_CONTINUE;
}

bool SceneSelectSetup::Render()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, { 0,0 }, &backgroundTextureRec, 0, 2);

	if (!isModeChosen) {
		App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
		App->renderer->Draw(*buttons_texture, { buttons_textureRec.x, buttons_textureRec.y }, { 0,0 }, &buttons_textureRec, 0, 2);

		App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
		float race_x = SCREEN_WIDTH / 2 - MeasureTextEx(App->assetLoader->titleFont, App->localization->GetString("SELECTMENU_MODE_RACE").c_str(), 100, 0).x/2;
		App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_RACE").c_str(), { race_x , race_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	
		float boom_x = SCREEN_WIDTH / 2 - MeasureTextEx(App->assetLoader->titleFont, App->localization->GetString("SELECTMENU_MODE_BOOM").c_str(), 100, 0).x/2;
		App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_BOOM").c_str(), { boom_x , boom_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	}
	if (!isCarChosen && isModeChosen) {
		App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
		App->renderer->Draw(*car_bg_texture, { car_bg_textureRec.x, car_bg_textureRec.y }, { 0,0 }, &car_bg_textureRec, 0, 2);
		
		//App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
		App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_FINISH").c_str(), { finish_car_button_textureRec.x , finish_car_button_textureRec.y }, finish_car_button_textOffset, App->assetLoader->titleFont, 100, 0, WHITE);

			if (currentVEHICLE == VEHICLES::CAR) {
				App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_CAR").c_str(), car_name_text_pos, {-MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_CAR").c_str(), 40, 0).x / 2,0}, App->assetLoader->agencyB, 40, 0, WHITE);
			}
			else if (currentVEHICLE == VEHICLES::MOTO) {
				App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_MOTO").c_str(), car_name_text_pos, {-MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_MOTO").c_str(), 40, 0).x / 2,0}, App->assetLoader->agencyB, 40, 0, WHITE);
			}
			else if (currentVEHICLE == VEHICLES::TRUCK) {
				App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_TRUCK").c_str(), car_name_text_pos, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_TRUCK").c_str(), 40, 0).x / 2,0 }, App->assetLoader->agencyB, 40, 0, WHITE);
			}
		}

	FadeRender();

	return true;
}

bool SceneSelectSetup::CleanUp()
{
	LOG("Unloading Select Setup");

	delete race_button;
	delete boom_button;
	delete finish_car_button;
	delete car_arrow_right;
	delete car_arrow_left;

	return true;
}

void SceneSelectSetup::ClickRACE()
{
	isModeChosen = true;
	currentMode = MODES::RACE;
}

void SceneSelectSetup::ClickBOOM()
{
	isModeChosen = true;
	currentMode = MODES::BOOM;
}

void SceneSelectSetup::OnMouseOverRACE()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*buttons_texture_hover, { race_buttonTextureRec.x , race_buttonTextureRec.y }, { 0,0 }, &buttons_texture_hover_section, 0, 2);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_CLASSIC_DESC").c_str(), {description_middle_pos.x - MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MODE_CLASSIC_DESC").c_str(), 40, 0).x/2 , description_middle_pos.y}, {0,0}, App->assetLoader->agencyB, 40, 0, WHITE);
}

void SceneSelectSetup::OnMouseOverBOOM()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*buttons_texture_hover, { boom_buttonTextureRec.x , boom_buttonTextureRec.y }, { 0,0 }, &buttons_texture_hover_section, 0, 2);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_BOOM_DESC").c_str(), {description_middle_pos.x - MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MODE_BOOM_DESC").c_str(), 40, 0).x/2 , description_middle_pos.y}, {0,0}, App->assetLoader->agencyB, 40, 0, WHITE);
}

void SceneSelectSetup::ClickFINISH()
{
	isCarChosen = true;
	finalVEHICLE = currentVEHICLE;
}

void SceneSelectSetup::OnMouseOverFINISH()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*finish_car_button_texture_hover, { finish_car_button_textureRec.x , finish_car_button_textureRec.y }, { 0,0 }, &finish_car_button_texture_hover_section, 0, 2);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_FINISH_DESC").c_str(), { description_middle_pos.x - MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_FINISH_DESC").c_str(), 40, 0).x / 2 , description_middle_pos.y }, { 0,0 }, App->assetLoader->agencyB, 40, 0, WHITE);

}

void SceneSelectSetup::ClickCarRightArrow()
{
	currentVEHICLE = (VEHICLES)(currentVEHICLE + 1);
	if (currentVEHICLE == VEHICLES::END) {
		currentVEHICLE = (VEHICLES)(VEHICLES::NONE + 1);
	}
}

void SceneSelectSetup::ClickCarLeftArrow()
{
	currentVEHICLE = (VEHICLES)(currentVEHICLE - 1);
	if (currentVEHICLE == VEHICLES::NONE) {
		currentVEHICLE = (VEHICLES)(VEHICLES::END - 1);
	}
}
