#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "SceneGame.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"

#include "Vehicle.h"
#include "FontCreator.h"
 

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

	car = new Vehicle(this, "moto-type2");
	
	//// Aqui ponemos todos los chars de la funete en orden
	std::vector<int> codepoints = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	' ', '.', ',', ':', ';', '\'', '\"', '_', '-'
	};

	font = FontCreator::GetInstance()->CreateFontFromTexture(*App->texture->GetTexture("Font1"), 6, 16, codepoints,0);
	return ret;
}

// Load assets
bool SceneGame::CleanUp()
{
	LOG("Unloading Intro scene");
	car->CleanUp();
	delete car;
	FontCreator::GetInstance()->DestroyFont(font);
	return true;
}

// Update: draw background
update_status SceneGame::Update()
{
	car->Update();
	car->Render();

	DrawTextEx(font, "Hola que tal estas rey\nquedaste 3_-2", { 100, 100 }, 90, 1, BLACK);

	return UPDATE_CONTINUE;
}
