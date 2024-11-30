#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "raylib.h"


ModuleAudio::ModuleAudio(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	music = Music{ 0 };
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;

    LOG("Loading raylib audio system");

    InitAudioDevice();

	return ret;
}

update_status ModuleAudio::Update()
{
	UpdateMusicStream(music);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

    // Unload sounds
	for (const auto& soundMapEntry : soundsMap) {
		for (const auto& sound : soundMapEntry.second.sounds) {
			UnloadSound(sound);
		}
	}
	soundsMap.clear();

    // Unload music
	StopMusicStream(music);
	UnloadMusicStream(music);

    CloseAudioDevice();

	return true;
}

// Play a music file
bool ModuleAudio::PlayMusic(std::string path)
{
	if(IsEnabled() == false)
		return false;

	bool ret = true;
	
    StopMusicStream(music);
    music = LoadMusicStream(path.c_str());
    
    PlayMusicStream(music);

	LOG("Successfully playing %s", path);

	return ret;
}

// Load WAV
unsigned int ModuleAudio::LoadFx(std::string path, bool loadEvenIfItExist)
{
	if(IsEnabled() == false)
		return -1;

	unsigned int ret = 0;

	for (const auto& soundMapEntry : soundsMap) {
		if (soundMapEntry.second.soundPath == path) {
			if (!loadEvenIfItExist) {
				ret = -1;
				LOG("Sound already loaded: %s", path);
			}
			else {
				ret = soundMapEntry.first;
			}
			break;
		}
	}
	
	if(ret!=-1){
		Sound sound = LoadSound(path.c_str());
		if (sound.stream.buffer == NULL)
		{
			LOG("Cannot load sound: %s", path);
		}
		else
		{
			if (ret == 0) {
				ret = soundsMap.size();
				soundsMap[ret] = SoundData{path};

			}
			soundsMap.at(ret).sounds.emplace_back(sound);
		}
	}

	return ret;
}

// Play WAV
bool ModuleAudio::PlayFx(unsigned int soundId, bool overrideIfSoundPlaying)
{
	if (IsEnabled() == false)
	{
		return false;
	}
	if (soundId == -1 || !IsSoundLoaded(soundId))
	{
		LOG("Sound not loaded: Id --> %d", soundId);
		return false;
	}

	bool ret = false;

	if (overrideIfSoundPlaying) {
		PlaySound(soundsMap.at(soundId).sounds.at(0));
		ret = true;
	}
	else {
		bool couldBePlayed = false;
		for (const auto& sound : soundsMap.at(soundId).sounds)
		{
			if (!IsSoundPlaying(sound)) {
				couldBePlayed = true;
				ret = true;
				PlaySound(sound);
				break;
			}
		}
		if (!ret)
			LOG("Sound could not be played: Id --> %d", soundId);
	}

	return ret;
}

bool ModuleAudio::IsSoundLoaded(int soundId)
{
	bool ret = false;

	ret = soundsMap.find(soundId) != soundsMap.end();

	return ret;
}
