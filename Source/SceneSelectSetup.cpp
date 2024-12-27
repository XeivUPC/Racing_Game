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

	// Buttons
	// Texture
	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons.png", "select_setup_mode_buttons");
	buttons_texture = App->texture->GetTexture("select_setup_mode_buttons");

	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons_hover.png", "select_setup_mode_buttons_hover");
	buttons_texture_hover = App->texture->GetTexture("select_setup_mode_buttons_hover");

	//Functionality
	race_button = new UIButton(this, { race_buttonTextureRec.x, race_buttonTextureRec.y }, { race_buttonTextureRec.width, race_buttonTextureRec.height });

	race_button->onMouseClick.emplace_back([&]() {ClickRACE(); });
	race_button->onMouseOver.emplace_back([&]() {OnMouseOverRACE(); });

	// Settings Button
	//Texture

	//Functionality
	boom_button = new UIButton(this, { boom_buttonTextureRec.x, boom_buttonTextureRec.y }, { boom_buttonTextureRec.width, boom_buttonTextureRec.height });

	boom_button->onMouseClick.emplace_back([&]() {ClickBOOM(); });
	boom_button->onMouseOver.emplace_back([&]() {OnMouseOverBOOM(); });

	return ret;
}

update_status SceneSelectSetup::Update()
{
	race_button->Update();
	boom_button->Update();

	Render();
	return UPDATE_CONTINUE;
}

bool SceneSelectSetup::Render()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*backgroundTexture, { backgroundTextureRec.x, backgroundTextureRec.y }, { 0,0 }, &backgroundTextureRec, 0, 2);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
	App->renderer->Draw(*buttons_texture, { buttons_textureRec.x, buttons_textureRec.y }, { 0,0 }, &buttons_textureRec, 0, 2);

	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_4);
	
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_RACE").c_str(), { race_buttonTextureRec.x , race_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);
	App->renderer->DrawText(App->localization->GetString("SELECTMENU_MODE_BOOM").c_str(), { boom_buttonTextureRec.x , boom_buttonTextureRec.y }, buttonsText_Offset, App->assetLoader->titleFont, 100, 0, WHITE);

	return true;
}

bool SceneSelectSetup::CleanUp()
{
	LOG("Unloading Select Setup");

	//delete race_button;
	//delete boom_button;

	return true;
}

void SceneSelectSetup::ClickRACE()
{
}

void SceneSelectSetup::ClickBOOM()
{
}

void SceneSelectSetup::OnMouseOverRACE()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*buttons_texture_hover, { race_buttonTextureRec.x , race_buttonTextureRec.y }, { 0,0 }, &buttons_texture_hover_section, 0, 2);
}

void SceneSelectSetup::OnMouseOverBOOM()
{
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_1);
	App->renderer->Draw(*buttons_texture_hover, { boom_buttonTextureRec.x , boom_buttonTextureRec.y }, { 0,0 }, &buttons_texture_hover_section, 0, 2);
}
