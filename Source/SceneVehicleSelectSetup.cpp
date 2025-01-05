#include "SceneVehicleSelectSetup.h"
#include "pugixml.hpp"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "SceneGame.h"
#include "ModuleAssetLoader.h"
#include "UIButton.h"
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
	setup = App->texture->GetTexture("UI_Bg");
	vehicles = App->texture->GetTexture(vehicleNames[currentVehicle].id);
	characters = App->texture->GetTexture("Characters");
	previousVehicle = new UIButton(this, { 200, 100 }, { 240, 50 });
	previousVehicle->onMouseClick.emplace_back([&]() {OnMouseClickPreviousVehicle();});
	previousVehicle->onMouseOver.emplace_back([&]() {OnMouseOverPreviousVehicle();});
	previousVehicle->onMouseExit.emplace_back([&]() {OnMouseExitPreviousVehicle();});

	nextVehicle = new UIButton(this, { 200, 490 }, { 240, 50 });
	nextVehicle->onMouseClick.emplace_back([&]() {OnMouseClickNextVehicle(); });
	nextVehicle->onMouseOver.emplace_back([&]() {OnMouseOverNextVehicle(); });
	nextVehicle->onMouseExit.emplace_back([&]() {OnMouseExitNextVehicle(); });

	previousCharacter = new UIButton(this, { 840, 100 }, { 240, 50 });
	previousCharacter->onMouseClick.emplace_back([&]() {OnMouseClickPreviousCharacter(); });
	previousCharacter->onMouseOver.emplace_back([&]() {OnMouseOverPreviousCharacter(); });
	previousCharacter->onMouseExit.emplace_back([&]() {OnMouseExitPreviousCharacter(); });

	nextCharacter = new UIButton(this, { 840, 490 }, { 240, 50 });
	nextCharacter->onMouseClick.emplace_back([&]() {OnMouseClickNextCharacter();});
	nextCharacter->onMouseOver.emplace_back([&]() {OnMouseOverNextCharacter();});
	nextCharacter->onMouseExit.emplace_back([&]() {OnMouseExitNextCharacter();});

	finish = new UIButton(this, { 320, 600 }, { 640, 50 });
	finish->onMouseClick.emplace_back([&]() {OnMouseClickFinish(); });
	finish->onMouseOver.emplace_back([&]() {OnMouseOverFinish(); });
	finish->onMouseExit.emplace_back([&]() {OnMouseExitFinish(); });
	return true;
}

update_status SceneVehicleSelectSetup::Update()
{
	previousVehicle->Update();
	nextVehicle->Update();
	previousCharacter->Update();
	nextCharacter->Update();
	finish->Update();

	Render();
	FadeUpdate();

	return UPDATE_CONTINUE;
}

bool SceneVehicleSelectSetup::Render()
{
	Rectangle rect = { 0, 0, 1280, 720 };
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_3);
	App->renderer->Draw(*setup, { 0,0 }, { 0,0 }, &rect, 0, 1);
	App->renderer->SelectRenderLayer(ModuleRender::RenderLayer::SUB_LAYER_2);
	App->renderer->DrawSimpleRectangle(previousVehicle->bounds, WHITE);
	App->renderer->DrawSimpleRectangle(nextVehicle->bounds, WHITE);
	App->renderer->DrawSimpleRectangle(previousCharacter->bounds, WHITE);
	App->renderer->DrawSimpleRectangle(nextCharacter->bounds, WHITE);
	App->renderer->DrawSimpleRectangle(finish->bounds, WHITE);

	App->renderer->Draw(*vehicles, { 320 - vehicleNames[currentVehicle].rectangle.width/2*5,320 - vehicleNames[currentVehicle].rectangle.height / 2 * 5 }, { 0,0 }, &vehicleNames[currentVehicle].rectangle, 0, 5);
	//App->renderer->DrawSimpleRectangle({200, 200, 240, 240}, WHITE);
	rect = characterRect;
	rect.x = rect.width * currentCharacter;
	App->renderer->Draw(*characters, { 840,200 }, { 0,0 }, &rect, 0, 5);
	//App->renderer->DrawSimpleRectangle({840, 200, 240, 240}, WHITE);
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
			VehicleData data = VehicleData{
				child.child("texture").attribute("name").as_string(),
				name,
				Rectangle{
					child.child("texture").attribute("pos-x").as_float(),
					child.child("texture").attribute("pos-y").as_float(),
					child.child("texture").attribute("size-x").as_float(),
					child.child("texture").attribute("size-y").as_float(),
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
	if (currentVehicle > 0)
		currentVehicle--;
}

void SceneVehicleSelectSetup::OnMouseOverPreviousVehicle()
{
}

void SceneVehicleSelectSetup::OnMouseExitPreviousVehicle()
{
}

void SceneVehicleSelectSetup::OnMouseClickNextVehicle()
{
	if (currentVehicle < vehicleNames.size()-1)
		currentVehicle++;
}

void SceneVehicleSelectSetup::OnMouseOverNextVehicle()
{
}

void SceneVehicleSelectSetup::OnMouseExitNextVehicle()
{
}

void SceneVehicleSelectSetup::OnMouseClickPreviousCharacter()
{
	if(currentCharacter > 0)
		currentCharacter--;
}

void SceneVehicleSelectSetup::OnMouseOverPreviousCharacter()
{
}

void SceneVehicleSelectSetup::OnMouseExitPreviousCharacter()
{
}

void SceneVehicleSelectSetup::OnMouseClickNextCharacter()
{
	if (currentCharacter < maxCharacters)
		currentCharacter++;
}

void SceneVehicleSelectSetup::OnMouseOverNextCharacter()
{
}

void SceneVehicleSelectSetup::OnMouseExitNextCharacter()
{
}

void SceneVehicleSelectSetup::OnMouseClickFinish()
{
	App->audio->PlayFx(App->assetLoader->audioMotorId);
	App->scene_game->SetPlayerVehicle(vehicleNames[currentVehicle].name);
	App->scene_game->SetVehicleType(vehicleType,vehicleNames.size()-1);
	StartFadeIn(App->scene_game, BLACK, 0.3f);
}

void SceneVehicleSelectSetup::OnMouseOverFinish()
{
}

void SceneVehicleSelectSetup::OnMouseExitFinish()
{
}
