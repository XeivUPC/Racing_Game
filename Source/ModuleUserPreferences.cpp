#include "Application.h"
#include "ModuleUserPreferences.h"
#include "ModuleLocalization.h"
#include "ModuleAudio.h"


ModuleUserPreferences::ModuleUserPreferences(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleUserPreferences::~ModuleUserPreferences()
{
}

bool ModuleUserPreferences::Init()
{
	LoadUserPreferences();
	return true;
}

bool ModuleUserPreferences::CleanUp()
{	
	SaveUserPreferences();
	return true;
}

void ModuleUserPreferences::LoadUserPreferences()
{
	pugi::xml_document preferencesFile;
	pugi::xml_parse_result result = preferencesFile.load_file(configPath.c_str());

	if (result)
	{
		LOG("config.xml parsed without errors");

		ModuleAudio* audio = App->audio;

		App->localization->ChangeLanguage((Language)preferencesFile.child("settings").child("language").attribute("value").as_int());

		pugi::xml_node volumesNode = preferencesFile.child("settings").child("volume");
		audio->ChangeGeneralVolume(volumesNode.child("general").attribute("value").as_float());
		audio->ChangeMusicVolume(volumesNode.child("music").attribute("value").as_float());
		audio->ChangeSfxVolume(volumesNode.child("sfx").attribute("value").as_float());

	}
	else
	{
		LOG("Error loading config.xml: %s", result.description());
	}
}

void ModuleUserPreferences::SaveUserPreferences()
{
	pugi::xml_document preferencesFile;
	pugi::xml_parse_result result = preferencesFile.load_file(configPath.c_str());

	if (result)
	{
		LOG("config.xml parsed without errors");

		ModuleAudio* audio = App->audio;


		preferencesFile.child("settings").child("language").attribute("value").set_value(App->localization->GetLanguage());

		pugi::xml_node volumesNode = preferencesFile.child("settings").child("volume");
		volumesNode.child("general").attribute("value").set_value(audio->GetGeneralVolume());
		volumesNode.child("music").attribute("value").set_value(audio->GetMusicVolume());
		volumesNode.child("sfx").attribute("value").set_value(audio->GetSfxVolume());

		preferencesFile.save_file(configPath.c_str());

	}
	else
	{
		LOG("Error loading config.xml: %s", result.description());
	}
}
