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
	
	//// General UI
	textureModule->CreateTexture("Assets/Textures/UI/UI_Background.png", "UI_Bg");

	textureModule->CreateTexture("Assets/Textures/UI/UI_SliderThumb.png", "UI_SliderThumb");
	textureModule->CreateTexture("Assets/Textures/UI/UI_Arrow.png", "UI_Arrow");
	textureModule->CreateTexture("Assets/Textures/UI/UI_PauseBackground.png", "UI_Pause_Bg");
	textureModule->CreateTexture("Assets/Textures/UI/UI_Button1.png", "UI_Btn1");

	//// Textures
	textureModule->CreateTexture("Assets/Textures/Cars.png", "Car");
	textureModule->CreateTexture("Assets/Textures/characters.png", "Characters");
	textureModule->CreateTexture("Assets/Textures/Motos.png", "Motos");
	textureModule->CreateTexture("Assets/Textures/Wheels.png", "Wheel");
	textureModule->CreateTexture("Assets/Textures/drift_mark.png", "DriftMark");
	textureModule->CreateTexture("Assets/Fonts/pixel_normal_6x11.png", "Font1");
	textureModule->CreateTexture("Assets/Fonts/agency_b_10x20.png", "agencyB");
	textureModule->CreateTexture("Assets/Fonts/title_font_30x50.png", "titleFont");
	//Intro
	textureModule->CreateTexture("Assets/Textures/UI/UI_Intro_Background.png", "UI_Intro_Bg");
	// Main Menu
	textureModule->CreateTexture("Assets/Textures/main_menu.png", "main_menu");
	textureModule->CreateTexture("Assets/Textures/main_menu_play_hover.png", "main_menu_play_hover");
	textureModule->CreateTexture("Assets/Textures/main_menu_settings_hover.png", "main_menu_settings_hover");
	// Select-Setup
	textureModule->CreateTexture("Assets/Textures/select_setup_background.png", "select_setup");
	textureModule->CreateTexture("Assets/Textures/select_setup_mode_buttons.png", "select_setup_mode_buttons");
	textureModule->CreateTexture("Assets/Textures/select_setup_mode_buttons_hover.png", "select_setup_mode_buttons_hover");
	textureModule->CreateTexture("Assets/Textures/select_setup_car_bg.png", "select_setup_car_bg");
	textureModule->CreateTexture("Assets/Textures/select_setup_mode_buttons_hover.png", "select_setup_mode_buttons_hover");
	textureModule->CreateTexture("Assets/Textures/select_setup_map_bg.png", "select_setup_map_bg");
	textureModule->CreateTexture("Assets/Textures/select_setup_map_button_hover.png", "select_setup_map_button_hover");
	// Options
	textureModule->CreateTexture("Assets/Textures/settings_menu.png", "backgroundSettings");
	textureModule->CreateTexture("Assets/Textures/settings_slider_thumb.png", "sliderThumbSettings");
	textureModule->CreateTexture("Assets/Textures/settings_arrow_right.png", "arrowSettings");
	textureModule->CreateTexture("Assets/Textures/settings_exit.png", "exitSettings");
	// Results
	textureModule->CreateTexture("Assets/Textures/Results_Background.png", "results_Background");
	textureModule->CreateTexture("Assets/Textures/Results_next_button.png", "results_next_button");

	// Game
	textureModule->CreateTexture("Assets/Textures/Map_1.png", "Map1");
	textureModule->CreateTexture("Assets/Textures/Map_1_Preview.png", "Map1_Preview");
	textureModule->CreateTexture("Assets/Textures/Map_2.png", "Map2");
	textureModule->CreateTexture("Assets/Textures/Map_2_Preview.png", "Map2_Preview");

	//// Audios
	audioMotorId = audioModule->LoadFx("Assets/Sounds/Sfx/MotorSFX.ogg");
	audioClickId = audioModule->LoadFx("Assets/Sounds/Sfx/Ui_Click.ogg");

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
	// hard-coding bc it does not recognise the characters
	192, 193, 200, 201, 204, 205, 210, 211, 217, 218,
	224, 225, 232, 233, 236, 237, 242, 243, 249, 250,
	'!', 161, 231, 209,'/', '*'
	};
	
	agencyB = FontCreator::GetInstance().CreateFontFromTexture(*textureModule->GetTexture("agencyB"), 10, 20, codepoints2, 0);

	std::vector<int> codepoints3 = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 210, 192, 193, 211, 218, 209
	};
	titleFont = FontCreator::GetInstance().CreateFontFromTexture(*textureModule->GetTexture("titleFont"), 30, 50, codepoints3, 0);

	return true;
}
