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

	textureModule->CreateTexture("Assets/Textures/Cars.png", "Car");
	textureModule->CreateTexture("Assets/Textures/Motos.png", "Motos");
	textureModule->CreateTexture("Assets/Textures/Wheels.png", "Wheel");
	textureModule->CreateTexture("Assets/Textures/drift_mark.png", "DriftMark");
	textureModule->CreateTexture("Assets/Fonts/pixel_normal_6x11.png", "Font1");
	return true;
}
