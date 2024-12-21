#include "Globals.h"
#include "Application.h"
#include "ModuleOptions.h"

ModuleOptions::ModuleOptions(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

// Destructor
ModuleOptions::~ModuleOptions()
{
}

bool ModuleOptions::Init()
{
	LOG("Init options");
	bool ret = true;

	return ret;
}

update_status ModuleOptions::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleOptions::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleOptions::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleOptions::CleanUp()
{
	LOG("Close Options");

	return true;
}
