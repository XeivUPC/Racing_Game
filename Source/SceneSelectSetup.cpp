#include "SceneSelectSetup.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
#include "ModuleLocalization.h"
#include "AnimationSystem.h"
#include "Timer.h"

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
	backgroundTexture = App->texture->GetTexture("select_setup");
	// Arrows
	arrows_texture = App->texture->GetTexture("arrowSettings");

	//// Select Buttons
	// Texture
	buttons_texture = App->texture->GetTexture("select_setup_mode_buttons");
	buttons_texture_hover = App->texture->GetTexture("select_setup_mode_buttons_hover");

	// Race button
	race_button = new UIButton(this, { race_buttonTextureRec.x, race_buttonTextureRec.y }, { race_buttonTextureRec.width, race_buttonTextureRec.height });
	race_button->onMouseClick.emplace_back([&]() {ClickRACE(); });
	race_button->onMouseOver.emplace_back([&]() {OnMouseOverRACE(); });

	// Boom button
	boom_button = new UIButton(this, { boom_buttonTextureRec.x, boom_buttonTextureRec.y }, { boom_buttonTextureRec.width, boom_buttonTextureRec.height });
	boom_button->onMouseClick.emplace_back([&]() {ClickBOOM(); });
	boom_button->onMouseOver.emplace_back([&]() {OnMouseOverBOOM(); });

	//// Car Selection
	//Texture
	car_bg_texture = App->texture->GetTexture("select_setup_car_bg");
	finish_car_button_texture_hover = App->texture->GetTexture("select_setup_mode_buttons_hover");

	// Finish car button
	finish_car_button = new UIButton(this, { finish_car_button_textureRec.x, finish_car_button_textureRec.y }, { finish_car_button_textureRec.width, finish_car_button_textureRec.height });
	finish_car_button->onMouseClick.emplace_back([&]() {ClickFINISH(); });
	finish_car_button->onMouseOver.emplace_back([&]() {OnMouseOverFINISH(); });

	// Right arrow button
	car_arrow_right = new UIButton(this, { car_arrow_right_rec.x, car_arrow_right_rec.y }, { car_arrow_right_rec.width, car_arrow_right_rec.height });
	car_arrow_right->onMouseClick.emplace_back([&]() {ClickCarRightArrow(); });
	car_arrow_right->onMouseOver.emplace_back([&]() {OverCarRightArrow(); });
	car_arrow_right->onMouseExit.emplace_back([&]() {ExitCarRightArrow(); });

	arrowRightSetupCarAnimator = new Animator(App);

	AnimationData arrowRightSetupCarIdle = AnimationData("arrowRightSetupCarIdle");
	arrowRightSetupCarIdle.AddSprite(Sprite{ arrows_texture,{0, 0}, {34,32} });

	AnimationData arrowRightSetupCarOver = AnimationData("arrowRightSetupCarOver");
	arrowRightSetupCarOver.AddSprite(Sprite{ arrows_texture,{1, 0}, {34,32} });

	AnimationData arrowRightSetupCarClick = AnimationData("arrowRightSetupCarClick");
	arrowRightSetupCarClick.AddSprite(Sprite{ arrows_texture,{2, 0}, {34,32} });

	arrowRightSetupCarAnimator->AddAnimation(arrowRightSetupCarIdle);
	arrowRightSetupCarAnimator->AddAnimation(arrowRightSetupCarOver);
	arrowRightSetupCarAnimator->AddAnimation(arrowRightSetupCarClick);
	arrowRightSetupCarAnimator->SetSpeed(0.1f);
	arrowRightSetupCarAnimator->SelectAnimation("arrowRightSetupCarIdle", true);

	// Left arrow button
	car_arrow_left = new UIButton(this, { car_arrow_left_rec.x, car_arrow_left_rec.y }, { car_arrow_left_rec.width, car_arrow_left_rec.height });
	car_arrow_left->onMouseClick.emplace_back([&]() {ClickCarLeftArrow(); });
	car_arrow_left->onMouseOver.emplace_back([&]() {OverCarLeftArrow(); });
	car_arrow_left->onMouseExit.emplace_back([&]() {ExitCarLeftArrow(); });

	arrowLeftSetupCarAnimator = new Animator(App);

	AnimationData arrowLeftSetupCarIdle = AnimationData("arrowLeftSetupCarIdle");
	arrowLeftSetupCarIdle.AddSprite(Sprite{ arrows_texture,{0, 0}, {34,32} });

	AnimationData arrowLeftSetupCarOver = AnimationData("arrowLeftSetupCarOver");
	arrowLeftSetupCarOver.AddSprite(Sprite{ arrows_texture,{1, 0}, {34,32} });

	AnimationData arrowLeftSetupCarClick = AnimationData("arrowLeftSetupCarClick");
	arrowLeftSetupCarClick.AddSprite(Sprite{ arrows_texture,{2, 0}, {34,32} });

	arrowLeftSetupCarAnimator->AddAnimation(arrowLeftSetupCarIdle);
	arrowLeftSetupCarAnimator->AddAnimation(arrowLeftSetupCarOver);
	arrowLeftSetupCarAnimator->AddAnimation(arrowLeftSetupCarClick);
	arrowLeftSetupCarAnimator->SetSpeed(0.1f);
	arrowLeftSetupCarAnimator->SelectAnimation("arrowLeftSetupCarIdle", true);

	//// Map Selection
	// Texture
	map_bg_texture = App->texture->GetTexture("select_setup_map_bg");
	finish_map_button_texture_hover = App->texture->GetTexture("select_setup_map_button_hover");

	// Finish map button
	finish_map_button = new UIButton(this, { finish_map_button_textureRec.x, finish_map_button_textureRec.y }, { finish_map_button_textureRec.width, finish_map_button_textureRec.height });
	finish_map_button->onMouseClick.emplace_back([&]() {ClickMapFINISH(); });
	finish_map_button->onMouseOver.emplace_back([&]() {OnMouseOverMapFINISH(); });

	// Right arrow button
	map_arrow_right = new UIButton(this, { map_arrow_right_rec.x, map_arrow_right_rec.y }, { map_arrow_right_rec.width, map_arrow_right_rec.height });
	map_arrow_right->onMouseClick.emplace_back([&]() {ClickMapRightArrow(); });
	map_arrow_right->onMouseOver.emplace_back([&]() {OverMapRightArrow(); });
	map_arrow_right->onMouseExit.emplace_back([&]() {ExitMapRightArrow(); });

	arrowRightSetupMapAnimator = new Animator(App);

	AnimationData arrowRightSetupMapIdle = AnimationData("arrowRightSetupMapIdle");
	arrowRightSetupMapIdle.AddSprite(Sprite{ arrows_texture,{0, 0}, {34,32} });

	AnimationData arrowRightSetupMapOver = AnimationData("arrowRightSetupMapOver");
	arrowRightSetupMapOver.AddSprite(Sprite{ arrows_texture,{1, 0}, {34,32} });

	AnimationData arrowRightSetupMapClick = AnimationData("arrowRightSetupMapClick");
	arrowRightSetupMapClick.AddSprite(Sprite{ arrows_texture,{2, 0}, {34,32} });

	arrowRightSetupMapAnimator->AddAnimation(arrowRightSetupMapIdle);
	arrowRightSetupMapAnimator->AddAnimation(arrowRightSetupMapOver);
	arrowRightSetupMapAnimator->AddAnimation(arrowRightSetupMapClick);
	arrowRightSetupMapAnimator->SetSpeed(0.1f);
	arrowRightSetupMapAnimator->SelectAnimation("arrowRightSetupMapIdle", true);

	// Left arrow button
	map_arrow_left = new UIButton(this, { map_arrow_left_rec.x, map_arrow_left_rec.y }, { map_arrow_left_rec.width, map_arrow_left_rec.height });
	map_arrow_left->onMouseClick.emplace_back([&]() {ClickMapLeftArrow(); });
	map_arrow_left->onMouseOver.emplace_back([&]() {OverMapLeftArrow(); });
	map_arrow_left->onMouseExit.emplace_back([&]() {ExitMapLeftArrow(); });

	arrowLeftSetupMapAnimator = new Animator(App);

	AnimationData arrowLeftSetupMapIdle = AnimationData("arrowLeftSetupMapIdle");
	arrowLeftSetupMapIdle.AddSprite(Sprite{ arrows_texture,{0, 0}, {34,32} });

	AnimationData arrowLeftSetupMapOver = AnimationData("arrowLeftSetupMapOver");
	arrowLeftSetupMapOver.AddSprite(Sprite{ arrows_texture,{1, 0}, {34,32} });

	AnimationData arrowLeftSetupMapClick = AnimationData("arrowLeftSetupMapClick");
	arrowLeftSetupMapClick.AddSprite(Sprite{ arrows_texture,{2, 0}, {34,32} });

	arrowLeftSetupMapAnimator->AddAnimation(arrowLeftSetupMapIdle);
	arrowLeftSetupMapAnimator->AddAnimation(arrowLeftSetupMapOver);
	arrowLeftSetupMapAnimator->AddAnimation(arrowLeftSetupMapClick);
	arrowLeftSetupMapAnimator->SetSpeed(0.1f);
	arrowLeftSetupMapAnimator->SelectAnimation("arrowLeftSetupMapIdle", true);

	StartFadeOut(BLACK, 0.3f);

	return ret;
}

update_status SceneSelectSetup::Update()
{
	if (!isModeChosen && !isCarChosen && !isMapChosen) {
		race_button->Update();
		boom_button->Update();
	}
	else if (isModeChosen && !isCarChosen && !isMapChosen) {
		finish_car_button->Update();
		car_arrow_right->Update();
		car_arrow_left->Update();
	}
	else if (isModeChosen && isCarChosen && !isMapChosen) {
		finish_map_button->Update();
		map_arrow_right->Update();
		map_arrow_left->Update();
	}
	FadeUpdate();

	Render();
	return UPDATE_CONTINUE;
}

bool SceneSelectSetup::Render()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, { 0,0 }, &backgroundTextureRec, 0, 2);

	if (!isModeChosen && !isCarChosen && !isMapChosen) {
		App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
		App->renderer->Draw(*buttons_texture, { buttons_textureRec.x, buttons_textureRec.y }, { 0,0 }, &buttons_textureRec, 0, 2);

		float race_x = SCREEN_WIDTH / 2 - MeasureTextEx(App->assetLoader->titleFont, App->localization->GetString("SELECTMENU_MODE_RACE").c_str(), 100, 0).x/2;
		if (App->localization->GetString("SELECTMENU_MODE_RACE").length() > 6) {
			race_x -= App->assetLoader->titleFont.recs->width;
		}
		App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_RACE").c_str(), { race_x , race_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	
		float boom_x = SCREEN_WIDTH / 2 - MeasureTextEx(App->assetLoader->titleFont, App->localization->GetString("SELECTMENU_MODE_BOOM").c_str(), 100, 0).x/2;
		App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_BOOM").c_str(), { boom_x , boom_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	}
	if (isModeChosen && !isCarChosen && !isMapChosen) {
		App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
		App->renderer->Draw(*car_bg_texture, { car_bg_textureRec.x, car_bg_textureRec.y }, { 0,0 }, &car_bg_textureRec, 0, 2);
		
		App->renderer->DrawText(App->localization->GetString("SELECTMENU_FINISH").c_str(), { finish_car_button_textureRec.x , finish_car_button_textureRec.y }, finish_car_button_textOffset, App->assetLoader->titleFont, 100, 0, WHITE);

		if (currentVEHICLE == VEHICLES::CAR) {
			App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_CAR").c_str(), car_name_text_pos, {-MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_CAR").c_str(), 40, 0).x / 2,0}, App->assetLoader->agencyB, 40, 0, BLACK);
		}
		else if (currentVEHICLE == VEHICLES::MOTO) {
			App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_MOTO").c_str(), car_name_text_pos, {-MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_MOTO").c_str(), 40, 0).x / 2,0}, App->assetLoader->agencyB, 40, 0, BLACK);
		}
		else if (currentVEHICLE == VEHICLES::TRUCK) {
			App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_TRUCK").c_str(), car_name_text_pos, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_TRUCK").c_str(), 40, 0).x / 2,0 }, App->assetLoader->agencyB, 40, 0, BLACK);
		}

		arrowRightSetupCarAnimator->Animate({ car_arrow_right_rec.x, car_arrow_right_rec.y }, { 0,0 }, 0, 1, false);
		arrowRightSetupCarAnimator->Update();
		if (arrowRightSetupCarAnimator->GetCurrentAnimationName() == "arrowRightSetupCarClick" && arrowRightSetupCarAnimator->HasAnimationFinished()) {
			arrowRightSetupCarAnimator->SelectAnimation("arrowRightSetupCarOver", true);
			justClickedarrowRightSetupCar = false;
		}

		arrowLeftSetupCarAnimator->Animate({ car_arrow_left_rec.x, car_arrow_left_rec.y }, { 0,0 }, 0, 1, true);
		arrowLeftSetupCarAnimator->Update();
		if (arrowLeftSetupCarAnimator->GetCurrentAnimationName() == "arrowLeftSetupCarClick" && arrowLeftSetupCarAnimator->HasAnimationFinished()) {
			arrowLeftSetupCarAnimator->SelectAnimation("arrowLeftSetupCarOver", true);
			justClickedarrowLeftSetupCar = false;
		}

	}
	if (isModeChosen && isCarChosen && !isMapChosen) {
		App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
		App->renderer->Draw(*map_bg_texture, { map_bg_textureRec.x, map_bg_textureRec.y }, { 0,0 }, &map_bg_textureRec, 0, 2);

		App->renderer->DrawText(App->localization->GetString("SELECTMENU_FINISH").c_str(), map_finish_text_pos, { -MeasureTextEx(App->assetLoader->titleFont, App->localization->GetString("SELECTMENU_FINISH").c_str(), 50, 0).x / 2, 0 }, App->assetLoader->titleFont, 50, 0, WHITE);

		if (currentMAP == MAPS::MAP1) {
			App->renderer->DrawText(App->localization->GetString("SELECTMENU_MAP1").c_str(), map_name_text_pos, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MAP1").c_str(), 40, 0).x / 2,0 }, App->assetLoader->agencyB, 40, 0, BLACK);
		}
		else if (currentMAP == MAPS::MAP2) {
			App->renderer->DrawText(App->localization->GetString("SELECTMENU_MAP2").c_str(), map_name_text_pos, {-MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MAP2").c_str(), 40, 0).x / 2,0}, App->assetLoader->agencyB, 40, 0, BLACK);
		}
		else if (currentMAP == MAPS::MAP3) {
			App->renderer->DrawText(App->localization->GetString("SELECTMENU_MAP3").c_str(), map_name_text_pos, { -MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MAP3").c_str(), 40, 0).x / 2,0 }, App->assetLoader->agencyB, 40, 0, BLACK);
		}

		arrowRightSetupMapAnimator->Animate({ map_arrow_right_rec.x, map_arrow_right_rec.y }, { 0,0 }, 0, 1, false);
		arrowRightSetupMapAnimator->Update();
		if (arrowRightSetupMapAnimator->GetCurrentAnimationName() == "arrowRightSetupMapClick" && arrowRightSetupMapAnimator->HasAnimationFinished()) {
			arrowRightSetupMapAnimator->SelectAnimation("arrowRightSetupMapOver", true);
			justClickedarrowRightSetupMap = false;
		}

		arrowLeftSetupMapAnimator->Animate({ map_arrow_left_rec.x, map_arrow_left_rec.y }, { 0,0 }, 0, 1, true);
		arrowLeftSetupMapAnimator->Update();
		if (arrowLeftSetupMapAnimator->GetCurrentAnimationName() == "arrowLeftSetupMapClick" && arrowLeftSetupMapAnimator->HasAnimationFinished()) {
			arrowLeftSetupMapAnimator->SelectAnimation("arrowLeftSetupMapOver", true);
			justClickedarrowLeftSetupMap = false;
		}
	}

	FadeRender();

	return true;
}

bool SceneSelectSetup::CleanUp()
{
	LOG("Unloading Select Setup");

	if (arrowRightSetupMapAnimator != nullptr) {
		delete arrowRightSetupMapAnimator;
		arrowRightSetupMapAnimator = nullptr;
	}
	if (arrowLeftSetupMapAnimator != nullptr) {
		delete arrowLeftSetupMapAnimator;
		arrowLeftSetupMapAnimator = nullptr;
	}
	if (arrowRightSetupCarAnimator != nullptr) {
		delete arrowRightSetupCarAnimator;
		arrowRightSetupCarAnimator = nullptr;
	}
	if (arrowLeftSetupCarAnimator != nullptr) {
		delete arrowLeftSetupCarAnimator;
		arrowLeftSetupCarAnimator = nullptr;
	}

	delete race_button;
	delete boom_button;
	delete finish_car_button;
	delete car_arrow_right;
	delete car_arrow_left;
	delete finish_map_button;
	delete map_arrow_right;
	delete map_arrow_left;

	return true;
}

void SceneSelectSetup::ClickRACE()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	isModeChosen = true;
	currentMode = MODES::RACE;

	StartFadeOut(BLACK, 0.3f);
}

void SceneSelectSetup::ClickBOOM()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	isModeChosen = true;
	currentMode = MODES::BOOM;

	StartFadeOut(BLACK, 0.3f);
}

void SceneSelectSetup::OnMouseOverRACE()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*buttons_texture_hover, { race_buttonTextureRec.x , race_buttonTextureRec.y }, { 0,0 }, &buttons_texture_hover_section, 0, 2);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_CLASSIC_DESC").c_str(), {description_middle_pos.x - MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MODE_CLASSIC_DESC").c_str(), 40, 0).x/2 , description_middle_pos.y}, {0,0}, App->assetLoader->agencyB, 40, 0, BLACK);
}

void SceneSelectSetup::OnMouseOverBOOM()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*buttons_texture_hover, { boom_buttonTextureRec.x , boom_buttonTextureRec.y }, { 0,0 }, &buttons_texture_hover_section, 0, 2);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_BOOM_DESC").c_str(), {description_middle_pos.x - MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MODE_BOOM_DESC").c_str(), 40, 0).x/2 , description_middle_pos.y}, {0,0}, App->assetLoader->agencyB, 40, 0, BLACK);
}

void SceneSelectSetup::ClickFINISH()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	isCarChosen = true;
	finalVEHICLE = currentVEHICLE;

	StartFadeOut(BLACK, 0.3f);
}

void SceneSelectSetup::OnMouseOverFINISH()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*finish_car_button_texture_hover, { finish_car_button_textureRec.x , finish_car_button_textureRec.y }, { 0,0 }, &finish_car_button_texture_hover_section, 0, 2);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_VEHICLE_FINISH_DESC").c_str(), { description_middle_pos.x - MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_VEHICLE_FINISH_DESC").c_str(), 40, 0).x / 2 , description_middle_pos.y }, { 0,0 }, App->assetLoader->agencyB, 40, 0, BLACK);
}

void SceneSelectSetup::ClickCarRightArrow()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	currentVEHICLE = (VEHICLES)(currentVEHICLE + 1);
	if (currentVEHICLE == VEHICLES::END_VEHICLE) {
		currentVEHICLE = (VEHICLES)(VEHICLES::NO_VEHICLE + 1);
	}
	arrowRightSetupCarAnimator->SelectAnimation("arrowRightSetupCarClick", false);
	justClickedarrowRightSetupCar = true;
}

void SceneSelectSetup::OverCarRightArrow()
{
	if (justClickedarrowRightSetupCar == true) return;
	arrowRightSetupCarAnimator->SelectAnimation("arrowRightSetupCarOver", false);
}

void SceneSelectSetup::ExitCarRightArrow()
{
	arrowRightSetupCarAnimator->SelectAnimation("arrowRightSetupCarIdle", false);
}

void SceneSelectSetup::ClickCarLeftArrow()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	currentVEHICLE = (VEHICLES)(currentVEHICLE - 1);
	if (currentVEHICLE == VEHICLES::NO_VEHICLE) {
		currentVEHICLE = (VEHICLES)(VEHICLES::END_VEHICLE - 1);
	}
	arrowLeftSetupCarAnimator->SelectAnimation("arrowLeftSetupCarClick", false);
	justClickedarrowLeftSetupCar = true;
}

void SceneSelectSetup::OverCarLeftArrow()
{
	if (justClickedarrowLeftSetupCar == true) return;
	arrowLeftSetupCarAnimator->SelectAnimation("arrowLeftSetupCarOver", false);
}

void SceneSelectSetup::ExitCarLeftArrow()
{
	arrowLeftSetupCarAnimator->SelectAnimation("arrowLeftSetupCarIdle", false);
}

void SceneSelectSetup::ClickMapFINISH()
{
	// Stop previous music
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	isMapChosen = true;
	finalMAP = currentMAP;

	StartFadeIn(App->scene_game, BLACK, 0.3f);
}

void SceneSelectSetup::OnMouseOverMapFINISH()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*finish_map_button_texture_hover, { finish_map_button_textureRec.x , finish_map_button_textureRec.y }, { 0,0 }, &finish_map_button_texture_hover_section, 0, 2);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_MAP_FINISH_DESC").c_str(), { description_middle_pos.x - MeasureTextEx(App->assetLoader->agencyB, App->localization->GetString("SELECTMENU_MAP_FINISH_DESC").c_str(), 40, 0).x / 2 , description_middle_pos.y }, { 0,0 }, App->assetLoader->agencyB, 40, 0, BLACK);
}

void SceneSelectSetup::ClickMapRightArrow()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	currentMAP = (MAPS)(currentMAP + 1);
	if (currentMAP == MAPS::END_MAP) {
		currentMAP = (MAPS)(MAPS::NO_MAP + 1);
	}
	arrowRightSetupMapAnimator->SelectAnimation("arrowRightSetupMapClick", false);
	justClickedarrowRightSetupMap = true;
}

void SceneSelectSetup::OverMapRightArrow()
{
	if (justClickedarrowRightSetupMap == true) return;
	arrowRightSetupMapAnimator->SelectAnimation("arrowRightSetupMapOver", true);
}

void SceneSelectSetup::ExitMapRightArrow()
{
	arrowRightSetupMapAnimator->SelectAnimation("arrowRightSetupMapIdle", true);
}

void SceneSelectSetup::ClickMapLeftArrow()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	currentMAP = (MAPS)(currentMAP - 1);
	if (currentMAP == MAPS::NO_MAP) {
		currentMAP = (MAPS)(MAPS::END_MAP - 1);
	}
	arrowLeftSetupMapAnimator->SelectAnimation("arrowLeftSetupMapClick", false);
	justClickedarrowLeftSetupMap = true;
}

void SceneSelectSetup::OverMapLeftArrow()
{
	if (justClickedarrowLeftSetupMap == true) return;
	arrowLeftSetupMapAnimator->SelectAnimation("arrowLeftSetupMapOver", true);
}

void SceneSelectSetup::ExitMapLeftArrow()
{
	arrowLeftSetupMapAnimator->SelectAnimation("arrowLeftSetupMapIdle", true);
}
