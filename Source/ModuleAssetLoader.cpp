#include "ModuleAssetLoader.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleAudio.h"
#include "FontCreator.h"

ModuleAssetLoader::ModuleAssetLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleAssetLoader::~ModuleAssetLoader()
{
	FontCreator::GetInstance().DestroyFont(basicFont);
}

bool ModuleAssetLoader::Init()
{
	ModuleTexture* textureModule = App->texture;
	ModuleAudio* audioModule = App->audio;

	//// Load All Requiered Files Here And Save The Returned Values If Requiered Inside The .hpp
	//// Textures
	textureModule->CreateTexture("Assets/Textures/Cars.png", "Car");
	textureModule->CreateTexture("Assets/Textures/Motos.png", "Motos");
	textureModule->CreateTexture("Assets/Textures/Wheels.png", "Wheel");
	textureModule->CreateTexture("Assets/Textures/drift_mark.png", "DriftMark");
	textureModule->CreateTexture("Assets/Fonts/pixel_normal_6x11.png", "Font1");

	//// Audios


	//// Fonts
	std::vector<int> codepoints = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	' ', '.', ',', ':', ';', '\'', '\"', '_', '-'
	};
	basicFont = FontCreator::GetInstance().CreateFontFromTexture(*textureModule->GetTexture("Font1"), 6, 16, codepoints, 0);

	return true;
}
