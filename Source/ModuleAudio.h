#pragma once

#include "Module.h"
#include <unordered_map>
#include <vector>
#include <string>


class ModuleAudio : public Module
{

	struct SoundData
	{
		std::string soundPath;
		std::vector<Sound> sounds;
	};


public:

	ModuleAudio(Application* app, bool start_enabled = true);
	~ModuleAudio();

	bool Init();
	update_status Update();
	bool CleanUp();

	// Play a music file
	bool PlayMusic(std::string path);

	// Load a sound in memory
	unsigned int LoadFx(std::string path, bool loadEvenIfItExist = false);

	// Play a previously loaded sound
	bool PlayFx(unsigned int soundId, bool overrideIfSoundPlaying = true);

	void ChangeGeneralVolume(float volume);
	void ChangeSfxVolume(float volume);
	void ChangeMusicVolume(float volume);

private:

	bool IsSoundLoaded(int soundId);

	Music music;

	/// Filters an array of Sounds by an ID
	std::unordered_map<unsigned int, SoundData> soundsMap;

	float general_volume = 1.0f;
	float sfx_volume = 1.0f;
	float music_volume = 1.0f;
};
