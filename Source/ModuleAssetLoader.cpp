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
	FontCreator::GetInstance().DestroyFont(agencyB);
	FontCreator::GetInstance().DestroyFont(titleFont);
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
	textureModule->CreateTexture("Assets/Fonts/agency_b_10x20.png", "agencyB");
	textureModule->CreateTexture("Assets/Fonts/title_font_30x50.png", "titleFont");
	// Main Menu
	App->texture->CreateTexture("Assets/Textures/main_menu.png", "main_menu");
	App->texture->CreateTexture("Assets/Textures/main_menu_play_hover.png", "main_menu_play_hover");
	App->texture->CreateTexture("Assets/Textures/main_menu_settings_hover.png", "main_menu_settings_hover");
	// Select-Setup
	App->texture->CreateTexture("Assets/Textures/select_setup_background.png", "select_setup");
	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons.png", "select_setup_mode_buttons");
	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons_hover.png", "select_setup_mode_buttons_hover");
	App->texture->CreateTexture("Assets/Textures/select_setup_car_bg.png", "select_setup_car_bg");
	App->texture->CreateTexture("Assets/Textures/select_setup_mode_buttons_hover.png", "select_setup_mode_buttons_hover");
	App->texture->CreateTexture("Assets/Textures/select_setup_map_bg.png", "select_setup_map_bg");
	App->texture->CreateTexture("Assets/Textures/select_setup_map_button_hover.png", "select_setup_map_button_hover");

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
	
	std::vector<int> codepoints2 = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	' ', '.', ',', ':', ';', '\'', '\"', '_', '-',
	'À', 'Á', 'È', 'É', 'Ì', 'Í', 'Ò', 'Ó', 'Ù', 'Ú',
	'à', 'á', 'è', 'é', 'ì', 'í', 'ò', 'ó', 'ù', 'ú',
	'!', '¡'
	};
	
	agencyB = FontCreator::GetInstance().CreateFontFromTexture(*textureModule->GetTexture("agencyB"), 10, 20, codepoints2, 0);

	std::vector<int> codepoints3 = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'Ò', 'À', 'Á', 'Ó', 'Ú'
	};
	titleFont = FontCreator::GetInstance().CreateFontFromTexture(*textureModule->GetTexture("titleFont"), 30, 50, codepoints3, 0);

	return true;
}
