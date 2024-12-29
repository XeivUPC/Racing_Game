#include "Application.h"
#include "ModuleLocalization.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>

ModuleLocalization::ModuleLocalization(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleLocalization::~ModuleLocalization()
{
}

bool ModuleLocalization::Start()
{
	ExtractData();
	return true;
}

bool ModuleLocalization::CleanUp()
{
	return true;
}

void ModuleLocalization::ChangeLanguage(Language language)
{
	currentLanguage = language;
}

Language ModuleLocalization::GetLanguage()
{
	return currentLanguage;
}

std::string ModuleLocalization::GetString(const std::string& key)
{
	if (localizedStrings.count(key) == 0)
		return key;
	return localizedStrings[key][currentLanguage];
}

std::string ModuleLocalization::FormatNumber(float number, int precision)
{
	std::stringstream ss;

	switch (currentLanguage) {
	case Language::ENGLISH:
		// Set locale for English (US)
		ss.imbue(std::locale("en_US.UTF-8"));
		ss << std::fixed << std::setprecision(precision) << number;
		break;

	case Language::SPANISH:
		// Set locale for Spanish (Spain)
		ss.imbue(std::locale("es_ES.UTF-8"));
		ss << std::fixed << std::setprecision(precision) << number;
		break;

	case Language::CATALAN:
		// Set locale for Catalan (Catalonia)
		ss.imbue(std::locale("ca_ES.UTF-8"));
		ss << std::fixed << std::setprecision(precision) << number;
		break;

	default:
		ss << "Unknown language format";
	}

	return ss.str();
}

void ModuleLocalization::ExtractData()
{
	std::string filename = "Assets/Data/LanguageTranslation.txt";
	std::ifstream file(filename);

	std::string content;

	std::string line;
	while (getline(file, line)) {
		content += line + "\n";
	}
	file.close();

	///////////////////////

	std::string value;

	std::vector<std::string> dataEntries;
	std::istringstream stringFullStream(content);
	while (getline(stringFullStream, value, '\n')) {
		dataEntries.emplace_back(value);
	}

	value = "";

	for (const auto& dataEntry : dataEntries) {
		std::vector<std::string> entryData;
		std::istringstream stringEntryStream(dataEntry);
		while (getline(stringEntryStream, value, '|')) {
			entryData.emplace_back(value);
		}
		std::string key = entryData[0];
		entryData.erase(entryData.begin());
		localizedStrings[key] = entryData;
	}
}