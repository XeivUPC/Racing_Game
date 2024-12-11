#include "ModuleAssetLoader.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleAudio.h"

ModuleAssetLoader::ModuleAssetLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleAssetLoader::~ModuleAssetLoader()
{
}

bool ModuleAssetLoader::Init()
{
	ModuleTexture* textureModule = App->texture;
	ModuleAudio* audioModule = App->audio;

	//// Load All Requiered Files Here And Save The Returned Values If Requiered Inside The .hpp

	textureModule->CreateTexture("Assets/Textures/Car.png", "Car");
	textureModule->CreateTexture("Assets/Textures/Wheel.png", "Wheel");
	return true;
}
