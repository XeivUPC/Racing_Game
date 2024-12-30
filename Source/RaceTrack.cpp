#include "RaceTrack.h"
#include "Application.h"
#include "ModuleRender.h"

#include <pugixml.hpp>

using namespace pugi;

RackTrack::RackTrack(Module* moduleAt, string trackPath) : MapObject(moduleAt)
{
	this->trackPath = trackPath;

	LoadTrack();
}

RackTrack::~RackTrack()
{
}

update_status RackTrack::Update()
{
	return UPDATE_CONTINUE;
}

bool RackTrack::Render()
{
	moduleAt->App->renderer->Draw(*trackTexture, { 0,0 }, { 0,0 });
	return true;
}

bool RackTrack::CleanUp()
{
	for (const auto& collider : trackColliders) {
		delete collider;
	}
	trackColliders.clear();

	return true;
}

void RackTrack::LoadTrack()
{
	pugi::xml_document trackFile;
	pugi::xml_parse_result result = trackFile.load_file(trackPath.c_str());

	if (result)
	{
		LOG("config.xml parsed without errors");

	}
	else
	{
		LOG("Error loading config.xml: %s", result.description());
	}
}
