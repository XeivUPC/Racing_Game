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

	//// Load All Requiered Files Here
	

	return true;
}
