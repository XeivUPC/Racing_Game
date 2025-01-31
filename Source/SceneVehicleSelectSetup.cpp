#include "SceneVehicleSelectSetup.h"
#include "pugixml.hpp"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "SceneGame.h"
#include "ModuleAssetLoader.h"
#include "ModuleLocalization.h"
#include "UIButton.h"
#include <algorithm>
using namespace pugi;

SceneVehicleSelectSetup::SceneVehicleSelectSetup(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

SceneVehicleSelectSetup::~SceneVehicleSelectSetup()
{
}

bool SceneVehicleSelectSetup::Start()
{
	LoadVehicles();
	
	vehicleColor = WHITE;
	currentVehicle = 0;
	currentCharacter = 0;

	bg_texture = App->texture->GetTexture("UI_Bg");
	selectionSlots_texture = App->texture->GetTexture("UI_VehicleSelect_Slots");
	btn_texture = App->texture->GetTexture("UI_Btn1");
	vehicles = App->texture->GetTexture(vehicleNames[currentVehicle].id);
	characters = App->texture->GetTexture("Characters");

	previousVehicle = new UIButton(this, { 174, 194 }, { btn_rect.width,btn_rect.height });
	previousVehicle->onMouseClick.emplace_back([&]() {OnMouseClickPreviousVehicle();});
	previousVehicle->SetInteractionStatus(false);

	nextVehicle = new UIButton(this, { 174, 551 }, { btn_rect.width,btn_rect.height });
	nextVehicle->onMouseClick.emplace_back([&]() {OnMouseClickNextVehicle(); });
	if ((int)vehicleNames.size() == 1)
		nextVehicle->SetInteractionStatus(false);

	previousCharacter = new UIButton(this, { 802, 194 }, { btn_rect.width,btn_rect.height });
	previousCharacter->onMouseClick.emplace_back([&]() {OnMouseClickPreviousCharacter(); });
	previousCharacter->SetInteractionStatus(false);

	nextCharacter = new UIButton(this, { 802, 551 }, { btn_rect.width,btn_rect.height });
	nextCharacter->onMouseClick.emplace_back([&]() {OnMouseClickNextCharacter();});
	if(maxCharacters==1)
		nextCharacter->SetInteractionStatus(false);

	finish = new UIButton(this, { SCREEN_WIDTH / 2 -50, 408 -50 }, { 100, 100 });
	finish->onMouseClick.emplace_back([&]() {OnMouseClickFinish(); });

	for (size_t i = 0; i < availableColors.size(); i++)
	{
		UIButton* colorBtn;
		Vector2 positionBtn = colorBtnAnchor;
		positionBtn.y += i * colorBtnSize.y + i*4;

		colorBtn = new UIButton(this, positionBtn, colorBtnSize);
		Color color = availableColors[i];
		colorBtn->onMouseClick.emplace_back([&, color]() {ChangeVehicleColor(color); });
		colorBtns.emplace_back(colorBtn);
	}

	return true;
}

update_status SceneVehicleSelectSetup::Update()
{
	previousVehicle->Update();
	nextVehicle->Update();
	previousCharacter->Update();
	nextCharacter->Update();
	finish->Update();

	for (size_t i = 0; i < colorBtns.size(); i++)
	{
		colorBtns[i]->Update();
	}

	Render();
	FadeUpdate();

	return UPDATE_CONTINUE;
}

bool SceneVehicleSelectSetup::Render()
{
	Rectangle rect = { 0, 0, 1280, 720 };
	App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::DEFAULT);
	App->renderer->Draw(*bg_texture, { 0,0 }, { 0,0 });
	App->renderer->Draw(*selectionSlots_texture, { 0,0 }, { 0,0 });


	App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_1);

	string textValue = App->localization->GetString("VEHICLESELECT_VEHICLE");
	Vector2 textSize = MeasureTextEx(App->assetLoader->agencyB,textValue.c_str(),60,0);
	App->renderer->DrawText(textValue.c_str(), {325-textSize.x/2,90-textSize.y/2}, {0,0}, App->assetLoader->agencyB, 60, 0, WHITE);

	textValue = App->localization->GetString("VEHICLESELECT_CHARACTER");
	textSize = MeasureTextEx(App->assetLoader->agencyB, textValue.c_str(), 60, 0);
	App->renderer->DrawText(textValue.c_str(), { 954 - textSize.x / 2,90 - textSize.y / 2 }, { 0,0 }, App->assetLoader->agencyB, 60, 0, WHITE);

	DrawSelectionBtnTexture(previousVehicle);
	DrawSelectionBtnTexture(nextVehicle);
	DrawSelectionBtnTexture(previousCharacter);
	DrawSelectionBtnTexture(nextCharacter);


	App->renderer->DrawSimpleCircle({finish->bounds.x+ finish->bounds.width/2,finish->bounds.y+ finish->bounds.height/2}, 50, WHITE);

	textValue = App->localization->GetString("VEHICLESELECT_READY");
	textSize = MeasureTextEx(App->assetLoader->agencyB, textValue.c_str(), 30, 0);
	App->renderer->DrawText(textValue.c_str(), { finish->bounds.x + finish->bounds.width / 2.f - textSize.x / 2.f,finish->bounds.y + finish->bounds.height / 2.f - textSize.y / 2.f }, { 0,0 }, App->assetLoader->agencyB, 30, 0, BLACK);

	App->renderer->BlockRenderLayer(ModuleRender::RenderLayer::OVER_LAYER_2);

	App->renderer->Draw(*vehicles, { 326 - vehicleNames[currentVehicle].rectangle.width/2*4,408 - vehicleNames[currentVehicle].rectangle.height / 2 * 4 }, { 0,0 }, &vehicleNames[currentVehicle].rectangle, 0, 4,0,0,vehicleColor);
	App->renderer->Draw(*vehicles, { 326 - vehicleNames[currentVehicle].rectangle.width/2*4,408 - vehicleNames[currentVehicle].rectangle.height / 2 * 4 }, { 0,0 }, &vehicleNames[currentVehicle].fixedRectangle, 0, 4);
	rect = characterRect;
	rect.x = rect.width * currentCharacter;

	App->renderer->Draw(*characters, { 954-48*2.5f,408-48*2.5f}, { 0,0 }, &rect, 0, 5);

	for (size_t i = 0; i < colorBtns.size(); i++)
	{
		Vector2 positionBtn = colorBtnAnchor;
		positionBtn.y += i * colorBtnSize.y + i * 4;
		App->renderer->DrawSimpleRectangle({ positionBtn.x,positionBtn.y,colorBtnSize.x,colorBtnSize.y}, BLACK);
		App->renderer->DrawSimpleRectangle({ positionBtn.x+1,positionBtn.y+1,colorBtnSize.x-2,colorBtnSize.y-2}, availableColors[i]);

	}

	App->renderer->UnlockRenderLayer();
	return true;
}

bool SceneVehicleSelectSetup::CleanUp()
{
	vehicleNames.clear();


	delete previousVehicle;
	delete nextVehicle;
	delete previousCharacter;
	delete nextCharacter;
	delete finish;
	for (size_t i = 0; i < colorBtns.size(); i++)
	{
		delete colorBtns[i];
	}
	colorBtns.clear();
	return true;
}

void SceneVehicleSelectSetup::LoadVehicles()
{
	xml_document vehiclesFile;
	xml_parse_result result = vehiclesFile.load_file(configPath.c_str());

	if (result)
	{
		LOG("config.xml parsed without errors");

		for (pugi::xml_node child : vehiclesFile.child("vehicle").children()) {
			
			string name = child.name();
			if (name.find(vehicleType))
			{
				continue;
			}
			Rectangle rect{
				child.child("texture").attribute("pos-x").as_float(),
				child.child("texture").attribute("pos-y").as_float(),
				child.child("texture").attribute("size-x").as_float(),
				child.child("texture").attribute("size-y").as_float(),
			};
			VehicleData data = VehicleData{
				child.child("texture").attribute("name").as_string(),
				name,
				rect,
				Rectangle{
					rect.x,
					rect.y + rect.height,
					rect.width,
					rect.height,
				}
			};
			vehicleNames.emplace_back(data);
		}
	}
	else
	{
		LOG("Error loading config.xml: %s", result.description());
	}
}

void SceneVehicleSelectSetup::SetData(string prefix)
{
	vehicleType = prefix;
}

void SceneVehicleSelectSetup::OnMouseClickPreviousVehicle()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	previousVehicle->SetInteractionStatus(true);
	nextVehicle->SetInteractionStatus(true);
	if (currentVehicle > 0)
		currentVehicle--;
	if (currentVehicle == 0)
		previousVehicle->SetInteractionStatus(false);
}

void SceneVehicleSelectSetup::OnMouseClickNextVehicle()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	nextVehicle->SetInteractionStatus(true);
	previousVehicle->SetInteractionStatus(true);
	if (currentVehicle < (int)vehicleNames.size() - 1)
		currentVehicle++;
	if (currentVehicle == vehicleNames.size()-1)
		nextVehicle->SetInteractionStatus(false);
}
void SceneVehicleSelectSetup::OnMouseClickPreviousCharacter()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	previousCharacter->SetInteractionStatus(true);
	nextCharacter->SetInteractionStatus(true);
	if(currentCharacter > 0)
		currentCharacter--;
	if (currentCharacter == 0)
		previousCharacter->SetInteractionStatus(false);
}

void SceneVehicleSelectSetup::OnMouseClickNextCharacter()
{
	App->audio->PlayFx(App->assetLoader->audioClickId);
	nextCharacter->SetInteractionStatus(true);
	previousCharacter->SetInteractionStatus(true);
	if (currentCharacter < maxCharacters)
		currentCharacter++;
	if (currentCharacter == maxCharacters)
		nextCharacter->SetInteractionStatus(false);
}

void SceneVehicleSelectSetup::OnMouseClickFinish()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	App->scene_game->SetPlayerVehicle(vehicleNames[currentVehicle].name,vehicleColor);
	App->scene_game->SetVehicleType(vehicleType,vehicleNames.size());
	App->scene_game->SetPlayerCharacter(currentCharacter);
	StartFadeIn(App->scene_game, BLACK, 0.3f);
}

void SceneVehicleSelectSetup::DrawSelectionBtnTexture(UIButton* btn)
{
	if(!btn->CanBeInteracted())
		App->renderer->Draw(*btn_texture, { btn->bounds.x, btn->bounds.y }, { 0,0 }, &btn_rect_locked);
	else {
		switch (btn->GetState())
		{
		case UIButton::BUTTON_STATE::NORMAL:
			App->renderer->Draw(*btn_texture, { btn->bounds.x, btn->bounds.y }, { 0,0 }, &btn_rect);
			break;
		case UIButton::BUTTON_STATE::OVER:
			App->renderer->Draw(*btn_texture, { btn->bounds.x, btn->bounds.y }, { 0,0 }, &btn_rect_hover);
			break;
		case UIButton::BUTTON_STATE::PRESSED:
			App->renderer->Draw(*btn_texture, { btn->bounds.x, btn->bounds.y }, { 0,0 }, &btn_rect_pressed);
			break;

		default:
			App->renderer->Draw(*btn_texture, { btn->bounds.x, btn->bounds.y }, { 0,0 }, &btn_rect_pressed);
			break;
		}
	}
	
}

void SceneVehicleSelectSetup::ChangeVehicleColor(Color colorBtn)
{
	vehicleColor = colorBtn;
}
