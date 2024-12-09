#pragma once

#include "Module.h"
#include <string>
#include <unordered_map>
#include <vector>

enum Language {
	ENGLISH,
	SPANISH,
	CATALAN
};
class ModuleLocalization : public Module
{
public:
	ModuleLocalization(Application* app, bool start_enabled = true);
	~ModuleLocalization();

	bool Start();
	bool CleanUp();

	void ChangeLanguage(Language language);

	std::string GetString(const std::string& key);
	std::string FormatNumber(float number, int precision);

public:

private:
	void ExtractData();

private:
	Language currentLanguage= Language::ENGLISH;
	std::unordered_map<std::string, std::vector<std::string>> localizedStrings;
};

