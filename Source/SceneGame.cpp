#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleAssetLoader.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"

#include "Vehicle.h"
#include "RaceTrack.h"


SceneGame::SceneGame(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
	
}

SceneGame::~SceneGame()
{}

// Load assets
bool SceneGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	car = new Vehicle(this, "car-type1");
	track = new RaceTrack(this, "Assets/Map/Map_2.tmx");

	StartFadeOut(WHITE, 0.5f);
	return ret;
}

// Load assets
bool SceneGame::CleanUp()
{
	LOG("Unloading Intro scene");
	car->CleanUp();
	delete car;

	track->CleanUp();
	delete track;
	return true;
}

// Update: draw background
update_status SceneGame::Update()
{

	Vector2 moveInput = { 0,0 };

	if (IsKeyDown(KEY_W))
		moveInput.y += 1;
	if (IsKeyDown(KEY_S))
		moveInput.y -= 1;

	if (IsKeyDown(KEY_A))
		moveInput.x -= 1;
	if (IsKeyDown(KEY_D))
		moveInput.x += 1;


	car->SetInput(moveInput);

	car->Update();
	track->Update();

	App->renderer->camera.target = { (float)METERS_TO_PIXELS(car->GetPos().x),(float)METERS_TO_PIXELS(car->GetPos().y) };
	App->renderer->camera.offset = { GetScreenWidth()/2.f,GetScreenHeight()/2.f};
	
	/// Last Things To Do
	ModuleScene::FadeUpdate();
	Render();
	return UPDATE_CONTINUE;
}

bool SceneGame::Render()
{
	track->Render();
	car->Render();

	ModuleScene::FadeRender();
	return true;
}
